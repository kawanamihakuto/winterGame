#include "BossBattleState.h"
#include"BossBattleDeadAnimState.h"
#include"Player.h"
#include"Input.h"
#include<memory>
namespace
{
	constexpr float kSpeed = 3.0f;
}

void PlayerState::BossBattleState::Enter(Player& player)
{
	player.SetIsRight(true);
	player.OnInvincible();
	AttackDelay = 0;
}

void PlayerState::BossBattleState::Update(Player& player, Input& input)
{
	if (player.GetIsDead())
	{
		player.ChangeState(std::make_unique<PlayerState::BossBattleDeadAnimState>());
		return;
	}

	if (sizeCount_ <= 6.05)
	{
		sizeCount_ += 0.05;
		player.SetSize(sizeCount_);
		if (sizeCount_ >= 6.05)
		{
			player.SetIsPlayMovie(true);
		}
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
	vel = { 0,0 };
	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		vel.x -= kSpeed;
	}
	if (input.IsPressed("right"))
	{
		vel.x += kSpeed;
	}
	if (input.IsPressed("up"))
	{
		vel.y -= kSpeed;
	}
	if (input.IsPressed("down"))
	{
		vel.y += kSpeed;
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