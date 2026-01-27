#include "GameSceneUI.h"
#include"Application.h"
#include<DxLib.h>
GameSceneUI::GameSceneUI(int backToTitleGraphhandle):
backToTitleGraphHandle_(backToTitleGraphhandle)
{
}

GameSceneUI::~GameSceneUI()
{
}

void GameSceneUI::Init()
{

}

void GameSceneUI::Update()
{

}

void GameSceneUI::Draw()
{
	auto wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(backToTitleGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(200,32,0,0,srcX,srcY,0.5,0.0,backToTitleGraphHandle_,true);
}