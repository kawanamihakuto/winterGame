#include "MouthHoldState.h"
#include"../Player.h"
#include"../../System/Input.h"


void PlayerState::MouthHoldState::Enter(Player& player)
{
	player.SetGraph(player.GetImages().mouthHold);
}

void PlayerState::MouthHoldState::Update(Player& player, Input& input)
{
	Vector2 vel = player.GetVelocity();
	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		vel.x -= PlayerConstant::kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		vel.x += PlayerConstant::kMoveSpeed;
	}

	//摩擦処理
	vel.x *= PlayerConstant::kFriction;

	//速度制限
	if (vel.x >= PlayerConstant::kMaxSpeed)
	{
		vel.x = PlayerConstant::kMaxSpeed;
	}
	if (vel.x <= -PlayerConstant::kMaxSpeed)
	{
		vel.x = -PlayerConstant::kMaxSpeed;
	}

	player.SetVelocity(vel);

	player.UpdatePhysics();
}

void PlayerState::MouthHoldState::Exit(Player& player)
{
}