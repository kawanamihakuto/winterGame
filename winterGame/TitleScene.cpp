#include "TitleScene.h"
#include<DxLib.h>
#include"Input.h"
#include"GameScene.h"
#include"SceneController.h"
#include"Application.h"

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
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "TitleScene", 0xffffff);
}

void TitleScene::FadeDraw()
{
	
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w *0.5, wsize.h*0.5f, "TitleScene", 0xffffff);
	//フェード処理
	auto rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

TitleScene::TitleScene(SceneController& controller):Scene(controller)
{
	update_ = &TitleScene::FadeInUpdate;
	draw_ = &TitleScene::FadeDraw;
	frame_ = fade_interval;
}

void TitleScene::Update(Input& input)
{
	(this->* update_)(input);
}

void TitleScene::Draw()
{
	(this->*draw_)();
}
