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
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw)
{
	//ゲーム内画像ハンドル
	graphHandle_ = LoadGraph("data/kirby.png");
	assert(graphHandle_ > -1);

	//プレイヤー生成
	player_ = std::make_shared<Player>(graphHandle_);
	//歩く敵生成
	std::shared_ptr<WalkEnemy> we1 = std::make_shared<WalkEnemy>(Vector2{ 600,200 },graphHandle_, player_);
	std::shared_ptr<WalkEnemy> we2 = std::make_shared<WalkEnemy>(Vector2{ 700,200 },graphHandle_, player_);
	std::shared_ptr<WalkEnemy> we3 = std::make_shared<WalkEnemy>(Vector2{ 800,200 },graphHandle_, player_);
	enemies_.push_back(we1);
	enemies_.push_back(we2);
	enemies_.push_back(we3);

	camera_ = std::make_shared<Camera>();
	//フェード用のフレームを初期化
	frame_ = fade_interval;	
}

GameScene::~GameScene()
{
	//画像をすべてデリート
	DeleteGraph(graphHandle_);
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
	player_->Update(input);

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

	//エネミー全体のUpdate
	for (auto& enemy : enemies_)
	{
		enemy->Update();
	}
	//カメラのUpdate
	camera_->Update(*player_);

	//吸い込みオブジェクトの生成処理
	if (player_->GetGenerateInhale())
	{
		//吸い込みオブジェクトが生成されていなかったら
		if (!inhale_)
		{
			//吸い込みオブジェクト生成
			inhale_ = std::make_shared<Inhale>(player_->GetPosition(), graphHandle_);
			//初期化
			inhale_->Init(player_);
		}
		//吸い込みオブジェクトが生成済み&Activeじゃないなら
		else if (inhale_ && !inhale_->GetIsActive())
		{
			//初期化のみ
			inhale_->Init(player_);
		}
		//リクエスト返却
		player_->SetGenerateInhale(false);
	}
	
	//吸い込みオブジェクトがあったら
	if (inhale_)
	{
		//吸い込みオブジェクトのUpdate
		inhale_->Update(player_, enemies_);
	}

	//弾全体のUpdate
	for (auto& shot : shots_)
	{
		shot->Update(player_,enemies_);
	}

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
		player_->SetDeleteInhale(false);
	}

	//ボタンが押されたらフェードアウトを始める
	if (input.IsTriggered("ok"))
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
		controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
		return;
	}
}

void GameScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);
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
	for (auto& shot : shots_)
	{
		shot->Draw(*camera_);
	}
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