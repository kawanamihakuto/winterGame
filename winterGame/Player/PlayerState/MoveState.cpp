#include "MoveState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"IdleState.h"
#include"JumpState.h"
#include"InhaleState.h"
#include"SpitState.h"
void PlayerState::MoveState::Enter(Player& player)
{
	switch (player.GetMouthState())
	{
	case MouthState::empty:
		//口を閉じる
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthClosed);
		break;
	case MouthState::holdingEnemy:
		//ほおばり
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
		break;
	}
}

void PlayerState::MoveState::Update(Player& player, Input& input)
{
	switch (player.GetMouthState())
	{
	case MouthState::empty:

		//吸い込み入力が入っていたらInhale状態に切り替える
		if (input.IsTriggered("attack"))
		{
			player.ChangeState(std::make_unique<InhaleState>());
			return;
		}
		break;
	case MouthState::holdingEnemy:
		if (input.IsTriggered("attack"))
		{
			player.ChangeState(std::make_unique<SpitState>());
			return;
		}
		break;
	}
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
	if (input.IsPressed("jump")&&player.GetIsGround())
	{
		player.ChangeState(std::make_unique<JumpState>());
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
