#include "PlayerMoveState.h"
#include"Player.h"
#include"../System/Input.h"
#include"PlayerIdleState.h"
#include"PlayerJumpState.h"
#include"PlayerInhaleState.h"

void PlayerMoveState::Enter(Player& player)
{
	//画像をMoveに変更
	player.SetGraph(player.GetImages().move);
}

void PlayerMoveState::Update(Player& player, Input& input)
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
		player.ChangeState(std::make_unique<PlayerJumpState>());
		return;
	}
	//吸い込み入力があったらInhale状態に切り替える
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<PlayerInhaleState>());
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
		player.ChangeState(std::make_unique<PlayerIdleState>());
	}

	player.UpdatePhysics();
}
void PlayerMoveState::Exit(Player& player)
{

}
