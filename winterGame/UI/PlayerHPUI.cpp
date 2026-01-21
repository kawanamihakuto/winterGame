#include "PlayerHPUI.h"
#include"Player.h"
#include"Camera.h"
#include"Application.h"
#include<DxLib.h>
PlayerHPUI::PlayerHPUI(int graphHandle):
	position_(100,670),
	graphHandle_(graphHandle)
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

	for (int i = 0; i < maxHp; i++)
	{
		DrawRectRotaGraph(wsize.w / 2 - 70 + i * 70, position_.y, 32, 0, 16, 16, 4, 0.0, graphHandle_, true);
		if (nowHp > i)
		{
			DrawRectRotaGraph(wsize.w / 2 - 70 + i*70,position_.y,0,0,16,16,4,0.0,graphHandle_,true);
		}
	}
}