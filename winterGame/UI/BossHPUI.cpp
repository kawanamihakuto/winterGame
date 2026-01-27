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
	auto wsize = Application::GetInstance().GetWindowSize();

	auto maxHp = boss.GetMaxHP();
	maxHp /= 10;
	auto nowHp = boss.GetHP();
	bool halfHp = false;

	//hp‚ª30‚Ì‚Æ‚«
	if (nowHp / 10 >= 3)
	{
		nowHp = 3;
	}
	//hp‚ª20‚©‚ç29‚Ì‚Æ‚«
	else if (nowHp / 10 == 2)
	{
		//25‚©‚ç29
		if (nowHp % 10 >= 5)
		{
			nowHp = 3;
		}
		//20‚©‚ç24
		else
		{
			nowHp = 2;
			halfHp = true;
		}
	}
	//hp‚ª10‚©‚ç19‚Ì‚Æ‚«
	else if (nowHp / 10 == 1)
	{
		//15‚©‚ç19
		if (nowHp % 10 >= 5)
		{
			nowHp = 2;
		}
		//10‚©‚ç14
		else
		{
			nowHp = 1;
			halfHp = true;
		}
	}
	//hp‚ª0‚©‚ç9‚Ì‚Æ‚«
	else if (nowHp / 10 == 0)
	{
		//5‚©‚ç9
		if (nowHp % 10 >= 5)
		{
			nowHp = 1;
		}
		//0‚©‚ç4
		else if(nowHp % 10 > 0)
		{
			nowHp = 0;
			halfHp = true;
		}
		else
		{
			nowHp = 0;
		}
	}

	for (int i = 0; i < maxHp; i++)
	{
		if (nowHp > i)
		{
			DrawRectRotaGraph(wsize.w * 0.8f - 70 + i * 70, position_.y, 0, 0, 16, 16, 4, 0.0, hpGraphHandle_, true);
		}
		else
		{
			if (halfHp)
			{
				DrawRectRotaGraph(wsize.w * 0.8f - 70 + i * 70, position_.y, 16, 0, 16, 16, 4, 0.0, hpGraphHandle_, true);
				break;
			}
		}
	}
}


