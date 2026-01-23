#include "GameoverScene.h"
#include<DxLib.h>
#include"Input.h"
#include"TitleScene.h"
#include"SceneController.h"
#include"Application.h"
#include"GameScene.h"
#include<cassert>

namespace
{
	constexpr int fade_interval = 60;
}

GameoverScene::GameoverScene(SceneController& controller, int stageNo) :Scene(controller),
stageNo_(stageNo)
{
	gameoverGraphHandle_ = LoadGraph("data/Gameover.png");
	assert(gameoverGraphHandle_ > -1);

	frame_ = fade_interval;
	count_ = 0;
	isFadeInOrFadeOut_ = true;
	update_ = &GameoverScene::FadeInUpdate;
	draw_ = &GameoverScene::FadeDraw;
}

GameoverScene::~GameoverScene()
{
	DeleteGraph(gameoverGraphHandle_);
}

void GameoverScene::FadeInUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		update_ = &GameoverScene::NormalUpdate;
		draw_ = &GameoverScene::NormalDraw;
		return;
	}
}

void GameoverScene::NormalUpdate(Input& input)
{
	if (isFadeInOrFadeOut_)
	{
		count_++;
		if (count_ >= 40)
		{
			isFadeInOrFadeOut_ = false;
		}
	}
	else
	{
		count_--;
		if (count_ <= 0)
		{
			isFadeInOrFadeOut_ = true;
		}
	}

	if (input.IsTriggered("ok"))
	{
		update_ = &GameoverScene::FadeOutUpdate;
		draw_ = &GameoverScene::FadeDraw;
		return;
	}
}

void GameoverScene::FadeOutUpdate(Input&)
{
	//フェードアウトし終わったらシーンを切り替える
	if (++frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_, stageNo_));
		return;
	}
}

void GameoverScene::NormalDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(gameoverGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 1.0, 0.0, gameoverGraphHandle_, true);
#ifdef _DEBUG
	DrawString(16, 16, "GameoverScene", 0xffffff);
#endif // _DEBUG
}

void GameoverScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(gameoverGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 1.0, 0.0, gameoverGraphHandle_, true);

	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GameoverScene::Update(Input& input)
{
	(this->*update_)(input);
}
void GameoverScene::Draw()
{
	(this->*draw_)();
}
