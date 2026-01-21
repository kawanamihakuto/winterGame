#include "BossIdleState.h"
#include<DxLib.h>
#include"Geometry.h"
#include"Lerp.h"
#include"BossBase.h"
namespace
{
	constexpr Vector2 kTopPos = {1000,100};
	constexpr Vector2 kMidPos = { 1000,600 };
	constexpr Vector2 kUnderPos = { 1000,1000 };
}

BossIdleState::BossIdleState():
	nextPos_(0),
	nowPosNo_(1)
{
}

BossIdleState::~BossIdleState()
{
}

void BossIdleState::Enter(BossBase& boss)
{
	//ç°ÇÃposNoà»äOÇÃílÇ™èoÇÈÇ‹Ç≈åJÇËï‘Ç∑
	while(true)
	{
		int num = GetRand(2);
		if (nowPosNo_ != num)
		{
			if (num == 0)
			{
				nextPos_ = kTopPos;
				break;
			}
			else if (num == 1)
			{
				nextPos_ = kMidPos;
				break;
			}
			else if (num == 2)
			{
				nextPos_ = kUnderPos;
				break;
			}
		}
	}
}

void BossIdleState::Update(BossBase& boss)
{
	Lerp lerp;
	auto pos = boss.GetPosition();
	pos = lerp.VLerp(pos, nextPos_, 0.1f);
	boss.SetPosition(pos);

	printfDx("nextPos\n");
}
void BossIdleState::Exit(BossBase& boss)
{

}