#include "PlayerJumpState.h"
#include"Player.h"
#include"../System/Input.h"
#include"PlayerIdleState.h"
#include"PlayerMoveState.h"
#include"PlayerInhaleState.h"
void PlayerJumpState::Enter(Player& player)
{
	//画像をJumpに変更
	player.SetGraph(player.GetImages().jump);
	// 上方向へ速度を与える
	Vector2 vel = player.GetVelocity();
	vel.y = -PlayerConstant::kJumpPower;
	player.SetVelocity(vel);
}

void PlayerJumpState::Update(Player& player, Input& input)
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

	auto pos = player.GetPosition();
	//地面に着地したらIdleかMoveへ遷移
	if (pos.y >= PlayerConstant::kGround)
	{
		if (input.IsPressed("left") || input.IsPressed("right"))
		{
			player.ChangeState(std::make_unique<PlayerMoveState>());
		}
		else
		{
			player.ChangeState(std::make_unique<PlayerIdleState>());
		}
	}
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<PlayerInhaleState>());
	}

}

void PlayerJumpState::Exit(Player& player)
{

}