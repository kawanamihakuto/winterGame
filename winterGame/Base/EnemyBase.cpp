#include "EnemyBase.h"
#include"../Actor/Player.h"
#include<memory>

constexpr int kGround = 400;

EnemyBase::EnemyBase(const int hp,const Vector2 vel,const Vector2 pos,EnemyImages& imgs, const int currentImage, std::shared_ptr<Player>player, bool isPlayerOnRight, int nockBackTime) :GameObject(pos),
hp_(hp),
velocity_(vel),
isDead_(false),
player_(player),
currentImage_(currentImage),
isPlayerOnRight_(isPlayerOnRight),
nockBackTime_(nockBackTime),
images_(imgs)
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
