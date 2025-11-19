#include "HitState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"IdleState.h"
#include"MoveState.h"
#include"InhaleState.h"
void PlayerState::HitState::Enter(Player& player)
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
void PlayerState::HitState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		player.ChangeState(std::make_unique<PlayerState::MoveState>());
	}
	else if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		player.ChangeState(std::make_unique<PlayerState::MoveState>());
	}
	else
	{
		player.ChangeState(std::make_unique<PlayerState::IdleState>());
	}

	if (input.IsPressed("inhale"))
	{

		player.ChangeState(std::make_unique<PlayerState::InhaleState>());
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