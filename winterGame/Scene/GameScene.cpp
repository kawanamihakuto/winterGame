#include "GameScene.h"
#include<DxLib.h>
#include"SceneController.h"
#include"Application.h"
#include"Input.h"
#include"GameoverScene.h"
#include"Player.h"
#include"WalkEnemy.h"
#include<cassert>
#include"Actor/Inhale.h"
#include"Camera.h"
#include"Actor/StarShot.h"
#include"Actor/AirShot.h"
#include"../Actor/PlayerInhaledRect.h"
#include"FlyEnemy.h"
#include"Stage/Stage.h"
#include"Actor/Door.h"
#include"ClearScene.h"
#include"UI/PlayerHPUI.h"
#include"UI/UIFrame.h"
#include"Bg.h"
#include"EffectManager.h"
#include"Item.h"
#include"../BossItem.h"
#include"SunBoss.h"
#include"BossHPUI.h"
#include"BossBullet.h"
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller,int stageNo) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw),
nowStageNo_(stageNo)
{
	//ゲーム内画像ハンドル
	graphHandle_ = LoadGraph("data/kirby.png");
	assert(graphHandle_ > -1);
	playerHpGraphHandle_ = LoadGraph("data/Heart.png");
	assert(playerHpGraphHandle_ > -1);
	UIFrameGraphHandle_ = LoadGraph("data/UIframe.png");
	assert(UIFrameGraphHandle_ > -1);
	skyGraphHandle_ = LoadGraph("data/SkyBg.png");
	assert(skyGraphHandle_ > -1);
	cloudGraphHandle_ = LoadGraph("data/CloudBg.png");
	assert(cloudGraphHandle_ > -1);
	sunGraphHandle_ = LoadGraph("data/SunBg.png");
	assert(sunGraphHandle_ > -1);
	itemGraphHandle_ = LoadGraph("data/Item.png");
	assert(itemGraphHandle_ > -1);
	sunBossGraphHandle_ = LoadGraph("data/SunBoss.png");
	assert(sunBossGraphHandle_ > -1);
	bossHpGraphHandle_ = LoadGraph("data/BossHeart.png");
	assert(bossHpGraphHandle_ > -1);
	playerTextGraphHandle_ = LoadGraph("data/Player.png");
	assert(playerTextGraphHandle_ > -1);
	bossTextGraphHandle_ = LoadGraph("data/Boss.png");
	assert(bossTextGraphHandle_ > -1);

	//フェード用のフレームを初期化
	frame_ = fade_interval;

	//ステージデータのロード
	stage_ = std::make_unique<Stage>();
	stage_->Init(graphHandle_, 16, 16);
	stage_->Load(nowStageNo_);

	//プレイヤー生成
	player_ = std::make_shared<Player>(graphHandle_);
	player_->Init(nowStageNo_);
	//エフェクトマネージャー
	effectManager_ = std::make_shared<EffectManager>(graphHandle_);
	//エネミー配置
	//エネミーの配置をクリアする
	enemies_.clear();
	assert(enemies_.empty() == true);
	const auto& spawns = stage_->GetEnemySpawns();
	for (const auto spawn : spawns)
	{
		if (spawn.type == 18)
		{
			enemies_.push_back(std::make_shared<WalkEnemy>(spawn.pos, graphHandle_, player_, effectManager_,spawn.isRight));
		}
		else if (spawn.type == 27)
		{
			enemies_.push_back(std::make_shared<FlyEnemy>(spawn.pos, graphHandle_, player_, effectManager_,spawn.isRight));
		}
	}
	//カメラ
	camera_ = std::make_shared<Camera>();
	camera_->Init(nowStageNo_);
	//ドア
	door_ = std::make_shared<Door>(graphHandle_);
	door_->Init(nowStageNo_);
	//プレイヤーHPUI
	playerHPUI_ = std::make_shared<PlayerHPUI>(playerHpGraphHandle_,playerTextGraphHandle_);
	//HPUIの枠
	UIFrame_ = std::make_shared<UIFrame>(UIFrameGraphHandle_);
	//背景
	bg_ = std::make_shared<Bg>(skyGraphHandle_, cloudGraphHandle_,sunGraphHandle_,(camera_->GetPosition().x - Application::GetInstance().GetWindowSize().w * 0.5f)* 0.5f);
	//ボスHPUI
	bossHPUI_ = std::make_shared<BossHPUI>(bossHpGraphHandle_,bossTextGraphHandle_);

	if (stageNo == 3)
	{
		items_.push_back(std::make_shared<BossItem>(player_, Vector2{ 1800,600 }, itemGraphHandle_));
	}
}

GameScene::~GameScene()
{
	//画像をすべてデリート
	DeleteGraph(graphHandle_);
	DeleteGraph(playerHpGraphHandle_);
	DeleteGraph(skyGraphHandle_);
	DeleteGraph(cloudGraphHandle_);
	DeleteGraph(sunGraphHandle_);
	DeleteGraph(itemGraphHandle_);
	DeleteGraph(sunBossGraphHandle_);
	DeleteGraph(bossHpGraphHandle_);
	DeleteGraph(playerTextGraphHandle_);
	DeleteGraph(bossTextGraphHandle_);
}

void GameScene::FadeInUpdate(Input&)
{
	//フェードインが終わったら状態を切り替える
	if (--frame_ <= 0)
	{
		update_ = &GameScene::NormalUpdate;
		draw_ = &GameScene::NormalDraw;
		return;
	}
}

void GameScene::NormalUpdate(Input& input)
{
	auto wsize = Application::GetInstance().GetWindowSize();

	//プレイヤーのUpdate
	player_->Update(input, *stage_);

	if (!player_->GetIsDead())
	{
		//エネミー全体のUpdate
		for (auto& enemy : enemies_)
		{
			enemy->Update(*stage_, *camera_);
		}
		//カメラのターゲットを設定
		camera_->SetTarget(player_->GetPosition());
		//カメラのUpdate
		camera_->Update();

		//吸い込みオブジェクトがあったら
		if (inhale_)
		{
			//吸い込みオブジェクトのUpdate
			inhale_->Update();
		}
		if (playerInhaledRect_)
		{
			playerInhaledRect_->Update();
		}
		//弾全体のUpdate
		for (auto& shot : shots_)
		{
			shot->Update(player_, enemies_, *stage_);
		}

		door_->Update();

		for (auto item : items_)
		{
			item->Update();
		}

		for (auto& boss : bosses_)
		{
			boss->Update();
		}

		for (auto bossBullet : bossBullets_)
		{
			bossBullet->Update(*camera_);
		}

		bg_->Update(*player_,*camera_);

		effectManager_->Update();
	}

	//弾の生成処理
	if (player_->GetIsSpit())
	{
		//弾の種類を判定
		switch (player_->GetStarOrAir())
		{
		case StarOrAir::star:
			//星弾を生成
			shots_.push_back(std::make_shared<StarShot>(player_->GetIsRight(), player_->GetPosition(), graphHandle_,effectManager_));
			break;
		case StarOrAir::air:
			//空気弾を生成
			shots_.push_back(std::make_shared<AirShot>(player_->GetIsRight(), player_->GetPosition(), graphHandle_,effectManager_));
			break;
		}
		//リクエスト返却
		player_->SetIsSpit(false);
	}

	//吸い込みオブジェクトと吸い込み中に出す当たり判定の生成処理
	if (player_->GetGenerateInhale())
	{
		//吸い込みオブジェクトが生成されていなかったら
		if (!inhale_)
		{
			//吸い込みオブジェクト生成
			inhale_ = std::make_shared<Inhale>(player_->GetPosition(), graphHandle_,player_);
			playerInhaledRect_ = std::make_shared<PlayerInhaledRect>(player_->GetPosition(), player_);
			//初期化
			inhale_->Init();
			playerInhaledRect_->Init();
		}
		//吸い込みオブジェクトが生成済み&Activeじゃないなら
		else if (inhale_ && !inhale_->GetIsActive())
		{
			//初期化のみ
			inhale_->Init();
			playerInhaledRect_->Init();
		}
	}
	//ボス生成
	if (player_->GetStartBossBattle())
	{
		bosses_.push_back(std::make_shared<SunBoss>(Vector2{2000,600},sunBossGraphHandle_,player_));
		player_->SetStartBossBattle(false);
	}

	for (auto boss : bosses_)
	{
		if (boss->GetShotFlag())
		{
			bossBullets_.push_back(std::make_shared<BossBullet>(boss->GetPosition(), player_->GetPosition(), sunBossGraphHandle_));
			bossBullets_.back()->Init();
			boss->ResetShotFlag();
		}
	}

	//-----------------------------
	//オブジェクト同士の衝突判定
	//-----------------------------
	//登録クリア
	collisionManager_.Clear();
	//プレイヤーを追加
	collisionManager_.Add(*player_);
	//エネミーの追加
	for (auto& enemy : enemies_)
	{
		collisionManager_.Add(*enemy);
	}
	//弾の追加
	for (auto& shot : shots_)
	{
		collisionManager_.Add(*shot);
	}
	//吸い込みオブジェクトの追加
	if (inhale_)
	{
		if (inhale_->GetIsActive())
		{
			collisionManager_.Add(*inhale_);
		}
	}
	if (playerInhaledRect_)
	{
		if (playerInhaledRect_->GetIsActive())
		{
			collisionManager_.Add(*playerInhaledRect_);
		}
	}

	collisionManager_.Add(*door_);

	for (auto item : items_)
	{
		collisionManager_.Add(*item);
	}

	for (auto boss : bosses_)
	{
		collisionManager_.Add(*boss);
	}

	for (auto bossBullet : bossBullets_)
	{
		collisionManager_.Add(*bossBullet);
	}

	//登録されたすべてのオブジェクトの当たり判定を行う
	collisionManager_.CheckAll();

	//-----------------------
	//オブジェクトの削除処理
	//-----------------------
	//エネミーの削除
	//remove_ifで消すべき要素を後ろに詰める
	auto newEnemyEnd = std::remove_if(
		enemies_.begin(),//vectorの最初の要素
		enemies_.end(),//vectorの最後の'次'の要素(end()に到達したらループ終了する)
		[](const std::shared_ptr<EnemyBase>& enemy)//ラムダ式(引数にremove_ifで現在の要素を渡す)
		{
			//死んでいるかどうかのフラグをチェック
			return enemy->GetIsDead();
		});
	//remove_ifで後ろに詰められた要素を消す
	enemies_.erase(newEnemyEnd, enemies_.end());

	//弾の削除
	auto newShotEnd = std::remove_if(
		shots_.begin(),
		shots_.end(),
		[](const std::shared_ptr<Shot>& shot)
		{
			return !shot->GetIsActive();
		});
	shots_.erase(newShotEnd, shots_.end());

	//アイテムの削除
	auto newItemEnd = std::remove_if(
		items_.begin(),
		items_.end(),
		[](const std::shared_ptr<Item>& item)
		{
			return !item->GetIsActive();
		});
	items_.erase(newItemEnd, items_.end());

	//ボスの削除
	auto newbossEnd = std::remove_if(
		bosses_.begin(),
		bosses_.end(),
		[](const std::shared_ptr<BossBase>& boss)
		{
			return !boss->GetIsActive();
		});
	bosses_.erase(newbossEnd, bosses_.end());
	//ボスの弾の削除
	auto newBossBulletEnd = std::remove_if(
		bossBullets_.begin(),
		bossBullets_.end(),
		[](const std::shared_ptr<BossBullet>& bossBullet)
		{
			return !bossBullet->GetIsActive();
		});
	bossBullets_.erase(newBossBulletEnd, bossBullets_.end());

	//吸い込みオブジェクトの削除
	if (player_->GetDeleteInhale())
	{
		inhale_->SetIsActive(false);
		playerInhaledRect_->SetIsActive(false);
	}

	//ボタンが押されたらフェードアウトを始める
	if (player_->GetIsCollisionDoor())
	{
		if (input.IsPressed("up"))
		{
			update_ = &GameScene::FadeOutUpdate;
			draw_ = &GameScene::FadeDraw;
		}
	}

	if (nowStageNo_ == 1)
	{
		if (player_->GetIsDead() && player_->GetPosition().y >= 1200)
		{
			update_ = &GameScene::FadeOutUpdate;
			draw_ = &GameScene::FadeDraw;
		}
	}
	else if (nowStageNo_ == 2)
	{
		if (player_->GetIsDead() && player_->GetPosition().y >= camera_->GetPosition().y + wsize.h / 2)
		{
			update_ = &GameScene::FadeOutUpdate;
			draw_ = &GameScene::FadeDraw;
		}
	}
	else if (nowStageNo_ == 3)
	{
		if (player_->GetIsDead() && player_->GetPosition().y <= -200)
		{
			update_ = &GameScene::FadeOutUpdate;
			draw_ = &GameScene::FadeDraw;
		}
	}
	
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_1))
	{
		nowStageNo_ = 1;
		ChangeStage(nowStageNo_);
	}
	else if (CheckHitKey(KEY_INPUT_2))
	{
		nowStageNo_ = 2;
		ChangeStage(nowStageNo_);
	}
	else if (CheckHitKey(KEY_INPUT_3))
	{
		nowStageNo_ = 3;
		ChangeStage(nowStageNo_);
	}
#endif // _DEBUG
}

void GameScene::FadeOutUpdate(Input&)
{
	//フェードアウトし終わったらシーンを切り替える
	if (++frame_ >= fade_interval)
	{
		if (player_->GetIsDead())
		{
			controller_.ChangeScene(std::make_shared<GameoverScene>(controller_,nowStageNo_));
			return;
		}
		else
		{
			if (nowStageNo_ == 1)
			{
				nowStageNo_++;
				ChangeStage(nowStageNo_);
				return;
			}
			else if (nowStageNo_ == 2)
			{
				nowStageNo_++;
				ChangeStage(nowStageNo_);
				return;
			}
			else if (nowStageNo_ == 3)
			{
				controller_.ChangeScene(std::make_shared<ClearScene>(controller_));
				return;
			}
		}
	}
}

void GameScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);

	bg_->Draw(nowStageNo_);

	stage_->Draw(*camera_);

	door_->Draw(*camera_);

	//プレイヤーのDraw
	player_->Draw(*camera_);
	//エネミー全体のDraw
	for (auto& enemy : enemies_)
	{
		enemy->Draw(*camera_);
	}
	//吸い込みオブジェクトがあったら
	if (inhale_)
	{
		//吸い込みオブジェクトのDraw
		inhale_->Draw(*camera_);
	}
	if (playerInhaledRect_)
	{
		playerInhaledRect_->Draw(*camera_);
	}
	for (auto& shot : shots_)
	{
		shot->Draw(*camera_);
	}

	//アイテム
	for (auto item : items_)
	{
		item->Draw(*camera_);
	}

	effectManager_->Draw(*camera_);

	UIFrame_->Draw();
	playerHPUI_->Draw(*player_);

	bossHPUI_->Draw();

	for (auto boss : bosses_)
	{
		bossHPUI_->Draw(*boss);
	}
	
	//フェード処理
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255 * rate);
}

void GameScene::NormalDraw()
{
	bg_->Draw(nowStageNo_);

	stage_->Draw(*camera_);

	door_->Draw(*camera_);

	//プレイヤーのDraw
	player_->Draw(*camera_);
	//エネミー全体のDraw
	for (auto& enemy : enemies_)
	{
		enemy->Draw(*camera_);
	}
	//吸い込みオブジェクトがあったら
	if (inhale_)
	{
		//吸い込みオブジェクトのDraw
		inhale_->Draw(*camera_);
	}
	if (playerInhaledRect_)
	{
		playerInhaledRect_->Draw(*camera_);
	}

	//アイテム
	for (auto item : items_)
	{
		item->Draw(*camera_);
	}

	for (auto boss : bosses_)
	{
		boss->Draw(*camera_);
	}

	for (auto& shot : shots_)
	{
		shot->Draw(*camera_);
	}

	for (auto bossBullet : bossBullets_)
	{
		bossBullet->Draw(*camera_);
	}

	effectManager_->Draw(*camera_);

	UIFrame_->Draw();
	playerHPUI_->Draw(*player_);

	bossHPUI_->Draw();
	for (auto boss : bosses_)
	{
		bossHPUI_->Draw(*boss);
	}
	
#ifdef _DEBUG
	DrawString(64, 64, "GameScene", 0xffffff);
	DrawFormatString(80, 80, 0xffffff, "stageNo:%d", nowStageNo_);
#endif // _DEBUG
}

void GameScene::Update(Input& input)
{
	//現在のUpdateを実行
	(this->*update_)(input);
}

void GameScene::Draw()
{
	//現在のDrawを実行
	(this->*draw_)();
}

void GameScene::ChangeStage(int stageNo)
{
	stage_->Init(graphHandle_, 16, 16);
	stage_->Load(stageNo);

	//エネミーの配置をクリアする
	enemies_.clear();
	assert(enemies_.empty() == true);

	const auto& spawns = stage_->GetEnemySpawns();

	for (const auto spawn : spawns)
	{
		if (spawn.type == 18)
		{
			enemies_.push_back(std::make_shared<WalkEnemy>(spawn.pos, graphHandle_, player_, effectManager_,spawn.isRight));
		}
		else if (spawn.type == 27)
		{
			enemies_.push_back(std::make_shared<FlyEnemy>(spawn.pos, graphHandle_, player_, effectManager_,spawn.isRight));
		}
	}

	player_->Init(stageNo);
	camera_->Init(stageNo);
	bg_->Init((camera_->GetPosition().x - Application::GetInstance().GetWindowSize().w * 0.5f) * 0.5f);
	door_->Init(stageNo);
	if (stageNo == 3)
	{
		items_.push_back(std::make_shared<BossItem>(player_, Vector2{ 1800,600 }, itemGraphHandle_));
	}
	update_ = &GameScene::FadeInUpdate;
	draw_ = &GameScene::FadeDraw;
}
