#include "AppearState.h"
#include"BossState/BossIdleState.h"
#include"BossState/NormalShotState.h"
#include"BossBase.h"
#include<memory>
#include"Lerp.h"
namespace
{
	constexpr float kSpeed = 3.0f;
	constexpr int kCountMax = 300;
}

BossState::AppearState::AppearState() :
	count_(kCountMax)
{
}

BossState::AppearState::~AppearState()
{
}

void BossState::AppearState::Enter(BossBase& boss)
{
}

void BossState::AppearState::Update(BossBase& boss)
{
	Lerp lerp;
	auto pos = boss.GetPosition();
	pos = lerp.VLerp(pos, { 2800,600 }, 0.01f);
	boss.SetPosition(pos);
	if (count_-- <= 0)
	{
		boss.SetModeChangeRequest(true);
		boss.ChangeState(std::make_unique<BossState::NormalShotState>());
	}

}

void BossState::AppearState::Exit(BossBase& boss)
{
}
