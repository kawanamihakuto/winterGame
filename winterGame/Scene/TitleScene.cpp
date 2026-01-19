#include "TitleScene.h"
#include<DxLib.h>
#include"Input.h"
#include"GameScene.h"
#include"SceneController.h"
#include"Application.h"
#include<cassert>
constexpr int fade_interval = 60;

void TitleScene::FadeInUpdate(Input&)
{
	if (--frame_ <= 0)
	{
		update_ = &TitleScene::NormalUpdate;
		draw_ = &TitleScene::NormalDraw;
		return;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("ok"))
	{
		update_ = &TitleScene::FadeOutUpdate;
		draw_ = &TitleScene::FadeDraw;
		frame_ = 0;
		return;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	if (++frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<GameScene>(controller_));
		return;
	}
}

void TitleScene::NormalDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;

	//背景画像描画
	GetGraphSize(bgHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 2.0, 0.0, bgHandle_, false);
	
	//タイトル画像描画
	GetGraphSize(titleGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.3f, 0, 0, srcX, srcY, 1.0, 0.0, titleGraphHandle_, true);
	
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

	auto rate = static_cast<float>(count_) / static_cast<float>(40);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	//pressAnyButton画像描画
	GetGraphSize(pressStartGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h, 0, 0, srcX, srcY, 1.0, 0.0, pressStartGraphHandle_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "TitleScene", 0xffffff);
#endif // _DEBUG
}

void TitleScene::FadeDraw()
{
	NormalDraw();
	//フェード処理
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

TitleScene::TitleScene(SceneController& controller):Scene(controller)
{
	titleGraphHandle_ = LoadGraph("data/title.png");
	assert(titleGraphHandle_ > -1);
	pressStartGraphHandle_ = LoadGraph("data/pressAnyButton.png");
	assert(pressStartGraphHandle_ > -1);
	bgHandle_ = LoadGraph("data/SkyBg.png");
	assert(bgHandle_ > -1);
	update_ = &TitleScene::FadeInUpdate;
	draw_ = &TitleScene::FadeDraw;
	frame_ = fade_interval;
	count_ = 0;
	isFadeInOrFadeOut_ = true;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleGraphHandle_);
}

void TitleScene::Update(Input& input)
{
	(this->* update_)(input);
}

void TitleScene::Draw()
{
	(this->*draw_)();
}
