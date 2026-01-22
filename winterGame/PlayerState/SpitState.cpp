#include "SpitState.h"
#include"Player.h"
#include"IdleState.h"

namespace
{
	constexpr int kSpitRecoveryCount = 40;
}

void PlayerState::SpitState::Enter(Player& player)
{
	player.SetMouthState(MouthState::empty);
	player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
	player.SetIsSpit(true);
	count_ = 0;
}

void PlayerState::SpitState::Update(Player& player, Input& input)
{
	count_++;
	if (count_ >= kSpitRecoveryCount)
	{
		player.ChangeState(std::make_unique<IdleState>());
	}
	else if (player.GetIsGround() && count_ >= kSpitRecoveryCount - 20)
	{
		player.ChangeState(std::make_unique<IdleState>());
	}
}

void PlayerState::SpitState::Exit(Player& player)
{
	
}