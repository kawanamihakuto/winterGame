#include "SwallowState.h"
#include"Player.h"
#include"IdleState.h"

void PlayerState::SwallowState::Enter(Player& player)
{
	player.SetMouthState(MouthState::empty);
}

void PlayerState::SwallowState::Update(Player& player, Input& input)
{
	player.ChangeState(std::make_unique<IdleState>());
}

void PlayerState::SwallowState::Exit(Player& player)
{
}
