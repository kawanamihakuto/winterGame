#include "NormalShotState.h"
#include"BossBase.h"
#include"Player.h"
BossState::NormalShotState::NormalShotState()
{
}

BossState::NormalShotState::~NormalShotState()
{
}

void BossState::NormalShotState::Enter(BossBase& boss)
{
	boss.OnShot();
}

void BossState::NormalShotState::Update(BossBase& boss)
{

}

void BossState::NormalShotState::Exit(BossBase& boss)
{

}