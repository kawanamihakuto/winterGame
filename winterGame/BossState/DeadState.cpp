#include "DeadState.h"
#include"BossBase.h"
#include<DxLib.h>

namespace
{
	constexpr float kShakePower = 10.0f;
	constexpr int kShakeTimeMax = 300;
}

BossState::DeadState::DeadState():
	shakeTime_(kShakeTimeMax)
{
}

BossState::DeadState::~DeadState()
{
}

void BossState::DeadState::Enter(BossBase& boss)
{
	boss.SetCameraShakeRequest(true);
}

void BossState::DeadState::Update(BossBase& boss)
{
	Vector2 shakeOffset = { 0.0f,0.0f };
	if (shakeTime_-- > 0)
	{
		auto power = kShakePower * (shakeTime_ / 300.0f);
		shakeOffset.x = GetRand(2000) / 1000.0f * power - power / 2;
		shakeOffset.y = GetRand(2000) / 1000.0f * power - power / 2;

		boss.SetOffset(shakeOffset);
	}
}

void BossState::DeadState::Exit(BossBase& boss)
{
}
