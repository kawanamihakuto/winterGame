#include "ClearScene.h"
#include"Input.h"
#include"TitleScene.h"
#include"Application.h"
#include"SceneController.h"
#include<DxLib.h>
#include"EffekseerForDXLib.h"
#include<cassert>

ClearScene::ClearScene(SceneController& controller) :Scene(controller)
{
	EffectHandle_ = LoadEffekseerEffect("data/fireworks.efk");
	assert(EffectHandle_ > -1);

	frame_ = 0;

	nowEffect_ = PlayEffekseer2DEffect(EffectHandle_);
}

ClearScene::~ClearScene()
{
	StopEffekseer2DEffect(nowEffect_);
	nowEffect_ = -1;
	DeleteEffekseerEffect(EffectHandle_);
}

void ClearScene::Update(Input& input)
{
	if (frame_++ >= 400)
	{
		frame_ = 0;

		nowEffect_ = PlayEffekseer2DEffect(EffectHandle_);
	}

	if (input.IsTriggered("ok"))
	{
		controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		return;
	}
}

void ClearScene::Draw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "ClearScene", 0xffffff);

	if (EffectHandle_ >= 0)
	{
		// 再生中のエフェクトを移動
		SetPosPlayingEffekseer2DEffect(nowEffect_, wsize.w / 2, wsize.h+200	, 0);

		// Effekseerにより再生中のエフェクトを更新する。
		UpdateEffekseer2D();

		// Effekseerにより再生中のエフェクトを描画する。
		DrawEffekseer2D();
	}
}
