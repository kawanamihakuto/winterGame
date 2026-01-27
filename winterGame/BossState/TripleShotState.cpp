#include "TripleShotState.h"
#include"Base/BossBase.h"
#include"GameScene.h"
namespace
{
	constexpr int kShotIntervalMax = 19;
	constexpr int kShotCountMax = 3;
}

BossState::TripleShotState::TripleShotState():
shotIntervalCount_(kShotIntervalMax),
shotCount_(kShotCountMax)
{
}

BossState::TripleShotState::~TripleShotState()
{
}

void BossState::TripleShotState::Enter(BossBase& boss)
{
	if (shotIntervalCount_-- <= 0)
	{
		if (shotCount_-- > 0)
		{
			shotIntervalCount_ = kShotIntervalMax;
			boss.OnShot();
			boss.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"bossShot" });
		}
	}	
}

void BossState::TripleShotState::Update(BossBase& boss)
{

}

void BossState::TripleShotState::Exit(BossBase& boss)
{

}
