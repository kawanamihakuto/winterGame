#include "HoveringState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"SpitState.h"
void PlayerState::HoveringState::Enter(Player& player)
{
	player.SetMouthState(MouthState::holdingAir);
	player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
	player.SetStarOrAir(StarOrAir::air);
	auto vel = player.GetVelocity();
	vel.y -= PlayerConstant::kHoveringPower;
	player.SetVelocity(vel);
}

void PlayerState::HoveringState::Update(Player& player,Input& input)
{
	auto vel = player.GetVelocity();
	if (input.IsTriggered("up"))
	{
		
		vel.y -= PlayerConstant::kHoveringPower;
	}
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		vel.x -= PlayerConstant::kMoveSpeed;
	}
	else if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		vel.x += PlayerConstant::kMoveSpeed;
	}

	//‘¬“x§ŒÀ
	if (vel.x >= PlayerConstant::kMaxSpeed)
	{
		vel.x = PlayerConstant::kMaxSpeed;
	}
	if (vel.x <= -PlayerConstant::kMaxSpeed)
	{
		vel.x = -PlayerConstant::kMaxSpeed;
	}

	vel.x *= PlayerConstant::kFriction;

	if (input.IsTriggered("attack"))
	{
		player.ChangeState(std::make_unique<SpitState>());
		return;
	}
	player.SetVelocity(vel);
	player.UpdatePhysics();
}

void PlayerState::HoveringState::Exit(Player& player)
{

}