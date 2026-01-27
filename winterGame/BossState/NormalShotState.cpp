#include "NormalShotState.h"
#include"BossBase.h"
#include"Player.h"
#include"GameScene.h"
BossState::NormalShotState::NormalShotState()
{
}

BossState::NormalShotState::~NormalShotState()
{
}

void BossState::NormalShotState::Enter(BossBase& boss)
{
	boss.OnShot();
	boss.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"bossShot" });
}

void BossState::NormalShotState::Update(BossBase& boss)
{

}

void BossState::NormalShotState::Exit(BossBase& boss)
{

}