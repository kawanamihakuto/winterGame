#include "EnemyBase.h"
#include"../Player/Player.h"
#include<memory>

constexpr int kGround = 400;

EnemyBase::EnemyBase(const int hp, const Vector2 vel, const Vector2 pos,const int handle, std::shared_ptr<Player>player, bool isPlayerOnRight, int nockBackTime) :GameObject(pos),
hp_(hp),
velocity_(vel),
isDead_(false),
player_(player),
isPlayerOnRight_(isPlayerOnRight),
nockBackTime_(nockBackTime),
graphHandle_(handle),
graphCutNo_(EnemyGraphCutNo::one)
{ 
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Gravity()
{
	velocity_.y += 0.5f;
}

void EnemyBase::ApplyMovement()
{
	position_ += velocity_;

	if (position_.y >= kGround)
	{
		position_.y = kGround;
		velocity_.y = 0.0f;
	}
}
