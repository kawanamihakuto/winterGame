#include "PlayerHitState.h"
#include"Player.h"
#include"../System/Input.h"
#include"PlayerIdleState.h"
#include"PlayerMoveState.h"
#include"PlayerInhaleState.h"
void PlayerHitState::Enter(Player& player)
{
	//hpÇå∏ÇÁÇ∑èàóù
	int hp = player.GetHp();
	hp -= 1;
	player.SetHp(hp);
#ifdef _DEBUG
	int rectColor = 0xff0000;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}
void PlayerHitState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		player.ChangeState(std::make_unique<PlayerMoveState>());
	}
	else if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		player.ChangeState(std::make_unique<PlayerMoveState>());
	}
	else
	{
		player.ChangeState(std::make_unique<PlayerIdleState>());
	}

	if (input.IsPressed("inhale"))
	{

		player.ChangeState(std::make_unique<PlayerInhaleState>());
	}
	player.UpdatePhysics();
}
void PlayerHitState::Exit(Player& player)
{
#ifdef _DEBUG
	int rectColor = 0x0000ff;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}