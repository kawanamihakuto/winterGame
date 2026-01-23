#include "HitStopState.h"
#include"Player.h"
#include"DeadAnimState.h"
namespace
{
	constexpr int kHitStopCountMax = 30;
}

void PlayerState::HitStopState::Enter(Player& player)
{
	HitStopCount_ = 0;
	player.SetVelocity({ 0.0f,0.0f });
	player.SetCameraShakeRequest(true);
}

void PlayerState::HitStopState::Update(Player& player, Input& inpit)
{
	HitStopCount_++;

	if (HitStopCount_ >= kHitStopCountMax)
	{
		player.ChangeState(std::make_unique<DeadAnimState>());
	}
}

void PlayerState::HitStopState::Exit(Player& player)
{
}
