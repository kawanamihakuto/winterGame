#include "GameScene.h"
#include<DxLib.h>
#include"SceneController.h"
#include"Application.h"
#include"Input.h"
#include"GameoverScene.h"
#include"Player.h"
#include"WalkEnemy.h"
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw)
{
	//idle
	//move
	//jump
	PlayerImages playerImgs
	{
		LoadGraph("data/player/Idle.png"),
		LoadGraph("data/player/Move.png"),
		LoadGraph("data/player/Jump.png")
	};

	//walk
	WalkEnemyImages walkEnemyImgs
	{
		LoadGraph("data/walkEnemy/Walk.png")
	};

	player_ = std::make_shared<Player>(playerImgs);
	walkEnemy_ = std::make_shared<WalkEnemy>(Vector2{800,200}, walkEnemyImgs,player_);
	frame_ = fade_interval;	
}

GameScene::~GameScene()
{
	
	DeleteGraph(player_->GetImages().idle);
	DeleteGraph(player_->GetImages().move);
	DeleteGraph(player_->GetImages().jump);
	DeleteGraph(walkEnemy_->GetImages().walk);
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
	player_->Update(input);
	walkEnemy_->Update();


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

	player_->Draw();
	walkEnemy_->Draw();
}

void GameScene::Update(Input& input)
{
	(this->*update_)(input);
}

void GameScene::Draw()
{
	(this->*draw_)();
}