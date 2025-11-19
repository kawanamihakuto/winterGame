#include "MoveState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"IdleState.h"
#include"JumpState.h"
#include"InhaleState.h"

void PlayerState::MoveState::Enter(Player& player)
{
	//画像をMoveに変更
	player.SetGraph(player.GetImages().move);
}

void PlayerState::MoveState::Update(Player& player, Input& input)
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
	//ジャンプ入力があったらJump状態に切り替える
	if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
		return;
	}
	//吸い込み入力があったらInhale状態に切り替える
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
		return;
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

	//速度がほぼ0になったらIdle状態に切り替える
	if (vel.x <= 0.1f && vel.x >= -0.1)
	{
		player.ChangeState(std::make_unique<IdleState>());
	}

	player.UpdatePhysics();
}
void PlayerState::MoveState::Exit(Player& player)
{

}
