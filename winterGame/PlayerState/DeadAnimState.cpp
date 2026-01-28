#include "DeadAnimState.h"
#include"Player.h"
#include"GameScene.h"
namespace
{
	constexpr int kUpCountMax = 30;
}

void PlayerState::DeadAnimState::Enter(Player& player)
{
	upCount_ = 0;
	player.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"playerDead" });
	player.GetScene()->PushRequest({ SceneRequestType::StopBGM,0.0f,0 });
}

void PlayerState::DeadAnimState::Update(Player& player, Input& inpit)
{
	upCount_++;
	auto angle = player.GetDeadAnimAngle();
	auto vel = player.GetVelocity();
	if (upCount_ >= kUpCountMax)
	{
		vel.y +=0.3;
	}
	else
	{
		vel.y = -5;
	}
	angle += 0.1;
	player.SetVelocity(vel);
	player.SetDeadAnimAngle(angle);
}

void PlayerState::DeadAnimState::Exit(Player& player)
{
}
