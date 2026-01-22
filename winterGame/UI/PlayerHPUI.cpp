#include "PlayerHPUI.h"
#include"Player.h"
#include"Camera.h"
#include"Application.h"
#include<DxLib.h>
PlayerHPUI::PlayerHPUI(int graphHandle,int textHandle):
	position_(100,685),
	hpGraphHandle_(graphHandle),
	textGraphHandle_(textHandle)
{
}

PlayerHPUI::~PlayerHPUI()
{
}

void PlayerHPUI::Init()
{
}

void PlayerHPUI::Update()
{
}

void PlayerHPUI::Draw(Player& player)
{
	auto maxHp = player.GetMaxHp();
	auto nowHp = player.GetHp();

	auto wsize = Application::GetInstance().GetWindowSize();

//	DrawBox(0,wsize.h - 100,wsize.w,wsize.h,0xeeeeee,true);
	int srcX, srcY;
	GetGraphSize(textGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.1f, position_.y - 3, 0, 0, srcX, srcY, 0.3, 0.0, textGraphHandle_, true);
	for (int i = 0; i < maxHp; i++)
	{
		DrawRectRotaGraph(wsize.w * 0.3f - 70 + i * 70, position_.y, 32, 0, 16, 16, 4, 0.0, hpGraphHandle_, true);
		if (nowHp > i)
		{
			DrawRectRotaGraph(wsize.w *0.3f - 70 + i*70,position_.y,0,0,16,16,4,0.0,hpGraphHandle_,true);
		}
	}
}