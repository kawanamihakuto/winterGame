#include<DxLib.h>
#include "Application.h"
#include"Input.h"
#include"SceneController.h"
#include"TitleScene.h"
#include"EffekseerForDXLib.h"
constexpr int kDefaultWindowWidth = 1280;//デフォルトウィンドウ幅
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

	SetDrawScreen(DX_SCREEN_BACK);


	//DirectX11を使用する設定
	//Effeksserを使用するには必ず設定する
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	//Effeksserを初期化する
	//引数は画面に表示する最大パーティクル数
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	//フルスクリーンウィンドウの切り替えでリソースが消えるのを防ぐ
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// Effekseerに2D描画の設定をする。
	Effekseer_Set2DSetting(windowSize_.w, windowSize_.h);

	// Zバッファを有効にする。
		// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	SetWriteZBuffer3D(TRUE);

	return true;
}

void Application::Run()
{
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

#ifdef _DEBUG
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
#endif // _DEBUG

		//ゲーム終了のリクエストがあればループを抜ける
		if (controller.GetGameEnd())
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
	Effkseer_End();
	DxLib_End();
}

const Size& Application::GetWindowSize()const
{
	return windowSize_;
}