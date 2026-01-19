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
		update_ = &TitleScene::FadeOutUpdate;
		draw_ = &TitleScene::FadeDraw;
		frame_ = 0;
		return;
	}

	if (input.IsTriggered("select"))
	{

	}
	
}

void TitleScene::FadeOutUpdate(Input&)
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	playerFadePosX_ += (wsize.w / 70.0f);

	if (playerFadePosX_ >= wsize.w * 1.8f)
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
	DrawRectRotaGraph(wsize.w * 0.6f, wsize.h * 0.4f, 0, 0, srcX, srcY, 1.0, 0.0, titleGraphHandle_, true);
	
	auto rate = static_cast<float>(count_) / static_cast<float>(40);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	//pressAnyButton画像描画
	GetGraphSize(pressStartGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.6f, wsize.h * 0.7, 0, 0, srcX, srcY, 1.2, 0.0, pressStartGraphHandle_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//プレイヤーフェード
	DrawRectRotaGraph(playerFadePosX_, wsize.h * 0.5f, 16, 0, 16, 16, 55.0, 0.0, gameGraphHandle_, true);

#ifdef _DEBUG
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "TitleScene", 0xffffff);
#endif // _DEBUG
}

void TitleScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	//背景画像描画
	GetGraphSize(bgHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 2.0, 0.0, bgHandle_, false);

	//タイトル画像描画
	GetGraphSize(titleGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.6f, wsize.h * 0.4f, 0, 0, srcX, srcY, 1.0, 0.0, titleGraphHandle_, true);

	auto rate = static_cast<float>(count_) / static_cast<float>(40);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	//pressAnyButton画像描画
	GetGraphSize(pressStartGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.6f, wsize.h * 0.7, 0, 0, srcX, srcY, 1.2, 0.0, pressStartGraphHandle_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//プレイヤーフェード
	DrawBox(playerFadePosX_, 0, playerFadePosX_ - wsize.w * 3, wsize.h, 0x000000, true);

	DrawRectRotaGraph(playerFadePosX_, wsize.h * 0.5f, 16, 0, 16, 16, 55.0, 0.0, gameGraphHandle_, true);

	auto rate2 = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate2);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

TitleScene::TitleScene(SceneController& controller):Scene(controller)
{
	titleGraphHandle_ = LoadGraph("data/title.png");
	assert(titleGraphHandle_ > -1);
	pressStartGraphHandle_ = LoadGraph("data/pressStartButton.png");
	assert(pressStartGraphHandle_ > -1);
	bgHandle_ = LoadGraph("data/SkyBg.png");
	assert(bgHandle_ > -1);
	gameGraphHandle_ = LoadGraph("data/kirby.png");
	assert(gameGraphHandle_ > -1);

	update_ = &TitleScene::FadeInUpdate;
	draw_ = &TitleScene::FadeDraw;
	frame_ = fade_interval;
	count_ = 0;
	isFadeInOrFadeOut_ = true;
	playerFadePosX_ = -30;
}

TitleScene::~TitleScene()
{
	DeleteGraph(titleGraphHandle_);
	DeleteGraph(pressStartGraphHandle_);
	DeleteGraph(gameGraphHandle_);
}

void TitleScene::Update(Input& input)
{
	(this->* update_)(input);
}

void TitleScene::Draw()
{
	(this->*draw_)();
}
