#include"DxLib.h"
#include "Application.h"
#include"Input.h"

constexpr int kDefaultWindowWidth = 640;//デフォルトウィンドウ幅
constexpr int kDefaultWindowHeight = 480;//デフォルトウィンドウ高さ
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
	SetWindowSize(windowSize_.w, windowSize_.h);
	ChangeWindowMode(true);

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

}