#include<DxLib.h>
#include "Application.h"
#include"Input.h"
#include"SceneController.h"
#include"TitleScene.h"
constexpr int kDefaultWindowWidth = 1080;//デフォルトウィンドウ幅
constexpr int kDefaultWindowHeight = 720;//デフォルトウィンドウ高さ
constexpr int kDefaultColorBit = 32;//デフォルトカラービット

Application::Application():
	windowSize_{kDefaultWindowWidth,kDefaultWindowHeight}
{

}

Application::~Application()
{

}

Application& Application::GetInstance()
{
	static Application instance;
	return instance;
}

bool Application::Init()
{
	//ウィンドウサイズ設定
	SetGraphMode(windowSize_.w, windowSize_.h, kDefaultColorBit);
	//ウィンドウモード設定
	ChangeWindowMode(true);
	//ウィンドウのタイトル設定
	SetMainWindowText("ゲーム名");

	if (DxLib_Init() == -1)
	{
		return false;
	}
	return true;
}

void Application::Run()
{
	SetDrawScreen(DX_SCREEN_BACK);
	Input input;//入力のためのオブジェクト
	SceneController controller;//シーン遷移のためのオブジェクト
	controller.ChangeScene(std::make_shared<TitleScene>(controller));

	
	while (ProcessMessage() != -1)
	{
		//このフレームの開始時間を取得
		LONGLONG start = GetNowHiPerformanceCount();

		ClearDrawScreen();
		//入力情報の更新
		input.Update();
		//シーンの更新
		controller.Update(input);
		//シーンの描画
		controller.Draw();

		

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		//フレームレート60に固定
		while (GetNowHiPerformanceCount() - start < 16667)
		{

		}
	}
}

void Application::Terminate()
{
	DxLib_End();
}

const Size& Application::GetWindowSize()const
{
	return windowSize_;
}