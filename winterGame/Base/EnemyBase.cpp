#include "EnemyBase.h"
#include"Player.h"
#include"WalkEnemy.h"
#include<memory>
#include"../System/Lerp.h"
constexpr int kGround = 400;
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
graphCutNo_(EnemyGraphCutNo::one),
isAlive_(true),
isInhaled_(false),
enemyType_(enemyType)
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
	return  CollisionLayers::kNormalPlayer |
			CollisionLayers::kInhale |
			CollisionLayers::kAttack |
			CollisionLayers::kInhaledPlayer;
}

void EnemyBase::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kNormalPlayer)
	{
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

	enemy.ApplyMovement();
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

	enemy.Gravity();

	enemy.SetVelocity(vel);

	enemy.ApplyMovement();

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
	enemy.Gravity();
	enemy.ApplyMovement();
}

void Inhaled::Exit(EnemyBase& enemy)
{
}