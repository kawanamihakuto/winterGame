#include "EnemyBase.h"
#include"Player.h"
#include"WalkEnemy.h"
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
graphCutNo_(EnemyGraphCutNo::one),
isAlive_(true),
isInhaled_(false)
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

Rect EnemyBase::GetColliderRect() const
{
	return rect_;
}

CollisionLayer EnemyBase::GetCollisionLayer() const
{
	if (!isAlive_)
	{
		return CollisionLayers::kNone;
	}
	return CollisionLayers::kEnemy;
}

CollisionLayer EnemyBase::GetHitMask() const
{
	return CollisionLayers::kPlayer | 
		   CollisionLayers::kInhale | 
		   CollisionLayers::kAttack;
}

void EnemyBase::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kPlayer)
	{
		if (isInhaled_)
		{
			ChangeState(std::make_unique<None>());
		}
		else if (!isInhaled_)
		{
			ChangeState(std::make_unique<Death>());
		}
		
	}
	if (other.GetCollisionLayer() & CollisionLayers::kInhale)
	{
		auto player =  GetPlayer();
		//プレイヤーが右にいるか左にいるかを判定
		float enemyToPlayer = player->GetPosition().x - position_.x;
		bool isplayerOnRight = enemyToPlayer > 0 ? true : false;
		SetPlayerOnRight(isplayerOnRight);

		//エネミーの状態遷移
		ChangeState(std::make_unique<Inhaled>());
	}

	if (other.GetCollisionLayer() & CollisionLayers::kAttack)
	{
		ChangeState(std::make_unique<None>());
	}
}
