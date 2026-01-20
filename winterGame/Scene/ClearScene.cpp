#include "ClearScene.h"
#include"Input.h"
#include"TitleScene.h"
#include"Application.h"
#include"SceneController.h"
#include<DxLib.h>
#include"EffekseerForDXLib.h"
#include<cassert>

namespace
{
	constexpr int fade_interval = 60;
}

ClearScene::ClearScene(SceneController& controller) :Scene(controller)
{
	EffectHandle_ = LoadEffekseerEffect("data/fireworks.efk");
	assert(EffectHandle_ > -1);
	bgHandle_ = LoadGraph("data/SkyBg.png");
	assert(bgHandle_ > -1);
	gameClearGraphHandle_ = LoadGraph("data/GameClear.png");
	assert(gameClearGraphHandle_ > -1);
	gameGraphHandle_ = LoadGraph("data/kirby.png");
	assert(gameGraphHandle_ > -1);
	pressStartGraphHandle_ = LoadGraph("data/pressStartButton.png");
	assert(pressStartGraphHandle_ > -1);

	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();

	playerFadePosX_ = wsize.w - 50;

	playerSrcX_ = 0;

	playerCount_ = 0;

	count_ = 0;

	nowEffect_ = PlayEffekseer2DEffect(EffectHandle_);

	update_ = &ClearScene::FadeInUpdate;
	draw_ = &ClearScene::FadeDraw;

	frame_ = fade_interval;

	pressStartWaitingCount_ = 0;

	isFadeInOrFadeOut_ = true;

	pressStartFadeCount_ = 0;
}

ClearScene::~ClearScene()
{
	StopEffekseer2DEffect(nowEffect_);
	nowEffect_ = -1;
	DeleteEffekseerEffect(EffectHandle_);
}

void ClearScene::FadeInUpdate(Input& input)
{
	if (--frame_ <= 0)
	{
		update_ = &ClearScene::NormalUpdate;
		draw_ = &ClearScene::NormalDraw;
		return;
	}
}

void ClearScene::NormalUpdate(Input& input)
{
	if (count_++ >= 400)
	{
		count_ = 0;

		nowEffect_ = PlayEffekseer2DEffect(EffectHandle_);
	}

	if (playerCount_++ >= 30)
	{
		playerCount_ = 0;
		playerSrcX_++;
		playerSrcX_ %= 2;
	}

	if (pressStartWaitingCount_++ >= 300)
	{
		if (isFadeInOrFadeOut_)
		{
			pressStartFadeCount_++;
			if (pressStartFadeCount_ >= 40)
			{
				isFadeInOrFadeOut_ = false;
			}
		}
		else
		{
			pressStartFadeCount_--;
			if (pressStartFadeCount_ <= 0)
			{
				isFadeInOrFadeOut_ = true;
			}
		}
	}

	if (pressStartWaitingCount_ >= 350)
	{
		if (input.IsTriggered("ok"))
		{
			update_ = &ClearScene::FadeOutUpdate;
			draw_ = &ClearScene::FadeDraw;
			return;
		}
	}
}

void ClearScene::FadeOutUpdate(Input& input)
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	playerFadePosX_ -= (wsize.w / 70.0f);

	if (playerFadePosX_ <= 0 - wsize.w * 0.8f)
	{
		controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		return;
	}
}

void ClearScene::NormalDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();

	int srcX, srcY;
	//背景画像描画
	GetGraphSize(bgHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 2.0, 0.0, bgHandle_, false);

	if (EffectHandle_ >= 0)
	{
		// 再生中のエフェクトを移動
		SetPosPlayingEffekseer2DEffect(nowEffect_, wsize.w*0.3f, wsize.h + 200, 0);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();

		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer2D();
	}

	//GameClear画像描画
	GetGraphSize(gameClearGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.35f, wsize.h * 0.4f, 0, 0, srcX, srcY, 1.3, 0.0, gameClearGraphHandle_, true);

	auto rate = static_cast<float>(pressStartFadeCount_) / static_cast<float>(40);
	if (pressStartWaitingCount_ >= 300)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
		//pressAnyButton画像描画
		GetGraphSize(pressStartGraphHandle_, &srcX, &srcY);
		DrawRectRotaGraph(wsize.w * 0.35f, wsize.h * 0.7, 0, 0, srcX, srcY, 1.2, 0.0, pressStartGraphHandle_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//プレイヤーフェード
	DrawRectRotaGraph(playerFadePosX_, wsize.h * 0.5f, playerSrcX_ * 16, 0, 16, 16, 55.0, 0.0, gameGraphHandle_, true , true);

#ifdef _DEBUG
	DrawString(16, 16, "ClearScene", 0xffffff);
#endif // _DEBUG
}

void ClearScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();

	int srcX, srcY;
	//背景画像描画
	GetGraphSize(bgHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f, wsize.h * 0.5f, 0, 0, srcX, srcY, 2.0, 0.0, bgHandle_, false);

	if (EffectHandle_ >= 0)
	{
		// 再生中のエフェクトを移動
		SetPosPlayingEffekseer2DEffect(nowEffect_, wsize.w * 0.3f, wsize.h + 200, 0);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();

		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer2D();
	}

	//GameClear画像描画
	GetGraphSize(gameClearGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.35f, wsize.h * 0.4f, 0, 0, srcX, srcY, 1.3, 0.0, gameClearGraphHandle_, true);

	auto rate = static_cast<float>(pressStartFadeCount_) / static_cast<float>(40);
	if (pressStartWaitingCount_ >= 300)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
		//pressAnyButton画像描画
		GetGraphSize(pressStartGraphHandle_, &srcX, &srcY);
		DrawRectRotaGraph(wsize.w * 0.35f, wsize.h * 0.7, 0, 0, srcX, srcY, 1.2, 0.0, pressStartGraphHandle_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//プレイヤーフェード
	DrawBox(playerFadePosX_, 0, playerFadePosX_ + wsize.w * 3, wsize.h, 0x000000, true);
	//プレイヤーフェード用画像描画
	DrawRectRotaGraph(playerFadePosX_, wsize.h * 0.5f, 16, 0, 16, 16, 55.0, 0.0, gameGraphHandle_, true,true);

	//フェード処理
	float rate2 = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate2);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void ClearScene::Update(Input& input)
{
	(this->*update_)(input);
}

void ClearScene::Draw()
{
	(this->*draw_)();
}
