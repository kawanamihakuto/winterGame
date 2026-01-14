#include "EnemyBase.h"
#include"Player.h"
#include"WalkEnemy.h"
#include<memory>
#include"../System/Lerp.h"
constexpr int kGround = 720;
constexpr int kSpeed = 1.5f;
constexpr int kMaxSpeed = 1.5f;
constexpr float kNockbackSpeed = 4.0f;
constexpr int kNockBackTimeMax = 20;

constexpr float kGravity = 0.5f;
//吸い込むときのLerpのtの値
constexpr float kInhaleLerpT = 0.05f;

EnemyBase::EnemyBase(const int hp, const Vector2 vel, const Vector2 pos,const int handle, std::shared_ptr<Player>player, bool isPlayerOnRight, int nockBackTime,EnemyType enemyType) :GameObject(pos),
hp_(hp),
velocity_(vel),
isDead_(false),
player_(player),
isPlayerOnRight_(isPlayerOnRight),
nockBackTime_(nockBackTime),
graphHandle_(handle),
graphCutNo_(0),
isAlive_(true),
isInhaled_(false),
enemyType_(enemyType),
isRight_(false),
counter_(0)
{ 
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Gravity()
{
	velocity_.y += 0.5f;
}

void EnemyBase::ApplyMovementX()
{
	position_.x += velocity_.x;
}

void EnemyBase::ApplyMovementY()
{
	position_.y += velocity_.y;
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
	return  CollisionLayers::kNormalPlayer |
			CollisionLayers::kInhale |
			CollisionLayers::kAttack |
			CollisionLayers::kInhaledPlayer;
}

void EnemyBase::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kNormalPlayer)
	{
		auto player = GetPlayer();
		//プレイヤーが右にいるか左にいるかを判定
		float enemyToPlayer = player->GetPosition().x - position_.x;
		bool isplayerOnRight = enemyToPlayer > 0 ? true : false;
		SetPlayerOnRight(isplayerOnRight);
		ChangeState(std::make_unique<Death>());
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

	if (other.GetCollisionLayer() & CollisionLayers::kInhaledPlayer)
	{
		ChangeState(std::make_unique<None>());
	}

	if (other.GetCollisionLayer() & CollisionLayers::kAttack)
	{
		ChangeState(std::make_unique<None>());
	}
}

void Move::Enter(EnemyBase& enemy)
{
}

void Move::Update(EnemyBase& enemy)
{
	Vector2 vel = enemy.GetVelocity();
	switch (enemy.GetEnemyType())
	{
	case EnemyType::walk:
		if (enemy.GetIsRight())
		{
			vel.x += kSpeed;
		}
		else
		{
			vel.x -= kSpeed;
		}
		

		if (vel.x >= kMaxSpeed)
		{
			vel.x = kMaxSpeed;
		}
		if (vel.x <= -kMaxSpeed)
		{
			vel.x = -kMaxSpeed;
		}

		enemy.SetVelocity(vel);
		break;
	case EnemyType::fly:
		vel.x -= kSpeed;

		if (vel.x >= kMaxSpeed)
		{
			vel.x = kMaxSpeed;
		}
		if (vel.x <= -kMaxSpeed)
		{
			vel.x = -kMaxSpeed;
		}

		enemy.SetVelocity(vel);
		break;
	}

	if (vel.x > 0)
	{
		enemy.OnRight();
	}
	else if (vel.x < 0)
	{
		enemy.OnLeft();
	}
}

void Move::Exit(EnemyBase& enemy)
{
}

void Death::Enter(EnemyBase& enemy)
{
	enemy.SetIsAlive(false);
}

void Death::Update(EnemyBase& enemy)
{
	switch (enemy.GetEnemyType())
	{
	case EnemyType::walk:
		enemy.Gravity();
		break;
	case EnemyType::fly:
		break;
	}
	Vector2 vel = enemy.GetVelocity();
	bool isPlayerOnRight = enemy.GetPlayerOnRight();

	if (isPlayerOnRight)
	{
		vel.x = -kNockbackSpeed;
	}
	else
	{
		vel.x = kNockbackSpeed;
	}

	enemy.SetVelocity(vel);

	auto nockBackTime = enemy.GetNockBackTime();
	nockBackTime += 1;
	if (nockBackTime >= kNockBackTimeMax)
	{
		enemy.ChangeState(std::make_unique<None>());
	}
	enemy.SetNockBackTime(nockBackTime);
}

void Death::Exit(EnemyBase& enemy)
{
}

void None::Enter(EnemyBase& enemy)
{
	//isDead_をtrueにする
	enemy.SetIsDead(true);
}

void None::Update(EnemyBase& enemy)
{
}

void None::Exit(EnemyBase& enemy)
{
}

void Inhaled::Enter(EnemyBase& enemy)
{
	enemy.SetIsInhaled(true);
	enemy.SetVelocity({ 0,0 });
}

void Inhaled::Update(EnemyBase& enemy)
{
	auto player = enemy.GetPlayer();
	Lerp lerp;
	//吸い込まれている敵の挙動をLerpで実装
	enemy.SetPosition(lerp.VLerp(enemy.GetPosition(), player->GetPosition(), kInhaleLerpT));
}

void Inhaled::Exit(EnemyBase& enemy)
{
}