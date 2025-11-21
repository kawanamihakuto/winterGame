#include "JumpState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"IdleState.h"
#include"MoveState.h"
#include"InhaleState.h"
void PlayerState::JumpState::Enter(Player& player)
{
	switch (player.GetMouthState())
	{
	case MouthState::Empty:
		//口を閉じる
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthClosed);
		break;
	case MouthState::Holding:
		//ほおばり
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
		break;
	}

	// 上方向へ速度を与える
	Vector2 vel = player.GetVelocity();
	vel.y = -PlayerConstant::kJumpPower;
	player.SetVelocity(vel);
}

void PlayerState::JumpState::Update(Player& player, Input& input)
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
			player.ChangeState(std::make_unique<MoveState>());
		}
		else
		{
			player.ChangeState(std::make_unique<IdleState>());
		}
	}
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

}

void PlayerState::JumpState::Exit(Player& player)
{

}