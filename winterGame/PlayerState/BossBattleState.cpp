#include "BossBattleState.h"
#include"Player.h"
#include"Input.h"
void PlayerState::BossBattleState::Enter(Player& player)
{
	player.SetIsRight(true);
	player.OnInvincible();
	AttackDelay = 0;
}

void PlayerState::BossBattleState::Update(Player& player, Input& input)
{
	if (sizeCount_ <= 6.05)
	{
		sizeCount_ += 0.05;
		player.SetSize(sizeCount_);
	}

	//攻撃
	if (input.IsPressed("attack") && AttackDelay >= 50)
	{
		player.SetStarOrAir(StarOrAir::star);
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
		player.SetIsSpit(true);
		AttackDelay = 0;
	}

	//攻撃
	if (input.IsTriggered("attack") && AttackDelay >= 20)
	{
		player.SetStarOrAir(StarOrAir::star);
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
		player.SetIsSpit(true);
		AttackDelay = 0;
	}

	if (AttackDelay++ >= 15)
	{
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthClosed);
	}

	auto vel = player.GetVelocity();
	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		vel.x -= PlayerConstant::kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		vel.x += PlayerConstant::kMoveSpeed;
	}
	if (input.IsPressed("up"))
	{
		vel.y -= PlayerConstant::kMoveSpeed;
	}
	if (input.IsPressed("down"))
	{
		vel.y += PlayerConstant::kMoveSpeed;
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
	if (vel.y >= PlayerConstant::kMaxSpeed)
	{
		vel.y = PlayerConstant::kMaxSpeed;
	}
	if (vel.y <= -PlayerConstant::kMaxSpeed)
	{
		vel.y = -PlayerConstant::kMaxSpeed;
	}

	//速度がほぼ0になったらIdle状態に切り替える
	if (!input.IsPressed("left")  &&
		!input.IsPressed("right") && 
		!input.IsPressed("up")    &&
		!input.IsPressed("down"))
	{
		vel = { 0.0f,0.0f };
	}

	player.SetVelocity(vel);
}

void PlayerState::BossBattleState::Exit(Player& player)
{

}