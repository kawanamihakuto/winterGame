#include "JumpState.h"
#include"Player.h"
#include"Input.h"
#include"IdleState.h"
#include"MoveState.h"
#include"InhaleState.h"
#include"SpitState.h"
#include"HoveringState.h"
void PlayerState::JumpState::Enter(Player& player)
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
	player.SetIsGround(false);
	// 上方向へ速度を与える
	Vector2 vel = player.GetVelocity();
	vel.y = -PlayerConstant::kJumpPower;
	player.SetVelocity(vel);

	player.OnJump();
}

void PlayerState::JumpState::Update(Player& player, Input& input)
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
		if (input.IsTriggered("up"))
		{
			player.ChangeState(std::make_unique<HoveringState>());
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

	auto pos = player.GetPosition();
	
	if (player.GetIsGround() == true)
	{
		player.ChangeState(std::make_unique<MoveState>());
	}

	if (input.IsTriggered("attack"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}
}

void PlayerState::JumpState::Exit(Player& player)
{

}