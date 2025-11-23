#include "SpitState.h"
#include"../Player.h"
#include"IdleState.h"
void PlayerState::SpitState::Enter(Player& player)
{
	player.SetMouthState(MouthState::empty);
	player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
	player.SetIsSpit(true);
}

void PlayerState::SpitState::Update(Player& player, Input& input)
{
	

	player.ChangeState(std::make_unique<IdleState>());
}

void PlayerState::SpitState::Exit(Player& player)
{
	
}