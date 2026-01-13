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
#include"PlayerHPUI.h"
#include"UIFrame.h"
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw)
{
	//ゲーム内画像ハンドル
	graphHandle_ = LoadGraph("data/kirby.png");
	assert(graphHandle_ > -1);
	playerHpGraphHandle_ = LoadGraph("data/Heart.png");
	assert(playerHpGraphHandle_ > -1);
	UIFrameGraphHandle_ = LoadGraph("data/UIframe.png");
	assert(UIFrameGraphHandle_ > -1);

	//フェード用のフレームを初期化
	frame_ = fade_interval;

	//ステージデータのロード
	stage_ = std::make_unique<Stage>();
	stage_->Load(1);
	stage_->Init(graphHandle_, 16, 16);
	//プレイヤー生成
	player_ = std::make_shared<Player>(graphHandle_);

	const auto& spawns = stage_->GetEnemySpawns();

	for (const auto spawn : spawns)
	{
		if (spawn.type == 18)
		{
			enemies_.push_back(std::make_shared<WalkEnemy>(spawn.pos, graphHandle_, player_));
		}
		else if (spawn.type == 27)
		{
			enemies_.push_back(std::make_shared<FlyEnemy>(spawn.pos, graphHandle_, player_));
		}
	}

	camera_ = std::make_shared<Camera>();

	door_ = std::make_shared<Door>(graphHandle_);

	playerHPUI_ = std::make_shared<PlayerHPUI>(playerHpGraphHandle_);

	UIFrame_ = std::make_shared<UIFrame>(UIFrameGraphHandle_);
}

GameScene::~GameScene()
{
	//画像をすべてデリート
	DeleteGraph(graphHandle_);
	DeleteGraph(playerHpGraphHandle_);
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
	}

	

	//弾の生成処理
	if (player_->GetIsSpit())
	{
		//弾の種類を判定
		switch (player_->GetStarOrAir())
		{
		case StarOrAir::star:
			//星弾を生成
			shots_.push_back(std::make_shared<StarShot>(player_->GetIsRight(), player_->GetPosition(), graphHandle_));
			break;
		case StarOrAir::air:
			//空気弾を生成
			shots_.push_back(std::make_shared<AirShot>(player_->GetIsRight(), player_->GetPosition(), graphHandle_));
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

	if (player_->GetIsDead() && player_->GetPosition().y >= 1200)
	{
		update_ = &GameScene::FadeOutUpdate;
		draw_ = &GameScene::FadeDraw;
	}
}

void GameScene::FadeOutUpdate(Input&)
{
	//フェードアウトし終わったらシーンを切り替える
	if (++frame_ >= fade_interval)
	{
		if (player_->GetIsDead())
		{
			controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
			return;
		}
		else
		{
			controller_.ChangeScene(std::make_shared<ClearScene>(controller_));
			return;
		}
	}
}

void GameScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);

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

	UIFrame_->Draw();
	playerHPUI_->Draw(*player_);

	//フェード処理
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255 * rate);
}

void GameScene::NormalDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);

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

	UIFrame_->Draw();
	playerHPUI_->Draw(*player_);
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