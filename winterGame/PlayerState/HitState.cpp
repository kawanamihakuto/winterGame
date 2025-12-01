#include "HitState.h"
#include"Player.h"
#include"Input.h"
#include"IdleState.h"
#include"MoveState.h"
#include"InhaleState.h"
#include"HoveringState.h"


void PlayerState::HitState::Enter(Player& player)
{
#ifdef _DEBUG
	int rectColor = 0xff0000;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}
void PlayerState::HitState::Update(Player& player, Input& input)
{
	player.NockBackTimeUpdate();

	if (player.IsNockBackEnd())
	{
		player.SetVelocity({ 0,0 });
		if (input.IsPressed("left"))
		{
			player.SetIsRight(false);
			player.ChangeState(std::make_unique<PlayerState::MoveState>());
			return;
		}
		else if (input.IsPressed("right"))
		{
			player.SetIsRight(true);
			player.ChangeState(std::make_unique<PlayerState::MoveState>());
			return;
		}

		if (input.IsTriggered("up"))
		{
			player.ChangeState(std::make_unique<PlayerState::HoveringState>());
			return;
		}

		if (input.IsTriggered("attack"))
		{
			player.ChangeState(std::make_unique<PlayerState::InhaleState>());
			return;
		}
	}

	player.UpdatePhysics();
}
void PlayerState::HitState::Exit(Player& player)
{
#ifdef _DEBUG
	int rectColor = 0x0000ff;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}