#include "BossIdleState.h"
#include<DxLib.h>
#include"Geometry.h"
#include"Lerp.h"
#include"BossBase.h"
#include "NormalShotState.h"
namespace
{
	constexpr Vector2 kTopPos = { 2800,400 };
	constexpr Vector2 kMidPos = { 2800,600 };
	constexpr Vector2 kUnderPos = { 2800,800 };
}

BossState::BossIdleState::BossIdleState() :
	nextPos_(0),
	nowPosNo_(1)
{
}

BossState::BossIdleState::~BossIdleState()
{
}

void BossState::BossIdleState::Enter(BossBase& boss)
{
	while (true)
	{
		int num = GetRand(2);

		if (num == 0 && num != nowPosNo_)
		{
			nextPos_ = kTopPos;
			nowPosNo_ = num;
			break;
		}
		else if (num == 1 && num != nowPosNo_)
		{
			nextPos_ = kMidPos;
			nowPosNo_ = num;
			break;
		}
		else if (num == 2 && num != nowPosNo_)
		{
			nextPos_ = kUnderPos;
			nowPosNo_ = num;
			break;
		}
	}
}

void BossState::BossIdleState::Update(BossBase& boss)
{
	Lerp lerp;
	auto pos = boss.GetPosition();
	pos = lerp.VLerp(pos, nextPos_, 0.02f);
	boss.SetPosition(pos);

	DrawFormatString(100, 100, 0xff00ff, "nextPos : %f,%f", nextPos_.x, nextPos_.y);
}
void BossState::BossIdleState::Exit(BossBase& boss)
{

}