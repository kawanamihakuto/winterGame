#include "SpitState.h"
#include"../Player.h"
#include"IdleState.h"
void PlayerState::SpitState::Enter(Player& player)
{
	player.SetMouthState(MouthState::Empty);
	player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
}

void PlayerState::SpitState::Update(Player& player, Input& input)
{
	player.ChangeState(std::make_unique<IdleState>());
}

void PlayerState::SpitState::Exit(Player& player)
{
	
}