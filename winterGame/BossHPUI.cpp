#include "BossHPUI.h"
#include"Base/BossBase.h"
#include"Application.h"
#include<DxLib.h>
BossHPUI::BossHPUI(int graphHandle,int textHandle):
	hpGraphHandle_(graphHandle),
	textGraphHandle_(textHandle),
	position_(100,685)
{
}

BossHPUI::~BossHPUI()
{
}

void BossHPUI::Init()
{

}

void BossHPUI::Update()
{

}

void BossHPUI::Draw()
{
	auto wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(textGraphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.6f, position_.y - 3, 0, 0, srcX, srcY, 0.3, 0.0, textGraphHandle_, true);

	for (int i = 0; i < 3; i++)
	{
		DrawRectRotaGraph(wsize.w * 0.8f - 70 + i * 70, position_.y, 32, 0, 16, 16, 4, 0.0, hpGraphHandle_, true);
	}
}

void BossHPUI::Draw(BossBase& boss)
{
	auto maxHp = boss.GetMaxHP();
	
	auto nowHp = boss.GetHP();

	auto wsize = Application::GetInstance().GetWindowSize();

	for (int i = 0; i < maxHp; i++)
	{
	//	DrawRectRotaGraph(wsize.w * 0.75f - 70 + i * 70, position_.y, 32, 0, 16, 16, 4, 0.0, graphHandle_, true);
		if (nowHp > i)
		{
			DrawRectRotaGraph(wsize.w * 0.8f - 70 + i * 70, position_.y, 0, 0, 16, 16, 4, 0.0, hpGraphHandle_, true);
		}
	}
}


