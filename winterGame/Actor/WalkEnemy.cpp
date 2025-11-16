#include<DxLib.h>
#include "WalkEnemy.h"
#include"../System/Rect.h"
#include"Player.h"
namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.5f;

	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	constexpr float kSize = 2.0f;

	constexpr float kGravity = 0.5f;
	constexpr int kGround = 400;
	constexpr float kMaxSpeed = 1.5f;

	constexpr float kNockbackSpeed = 3.0f;
	constexpr float kNockBackTimeMax = 20;
}

WalkEnemy::WalkEnemy(Vector2 pos,WalkEnemyImages& imgs,std::shared_ptr<Player>player) :EnemyBase(kHp,{0,0}, pos),
images_(imgs),
currentImage_(images_.walk),
player_(player),
isPlayerOnRight_(false),
nockBackTime_(0)
{
	state_ = std::make_unique<Walk>();
}

WalkEnemy::~WalkEnemy()
{
}

void WalkEnemy::Init()
{
	
}

void WalkEnemy::Update()
{
	state_->Update(*this);
}

void WalkEnemy::Draw()
{
	Vector2 pos = GetPosition();
	DrawRectRotaGraph(pos.x, pos.y, 0, 0, kWidth, kHeight, kSize,0, currentImage_, true);
	const Rect& rect = GetHitRect();
	rect.Draw(0x0000ff,false);
}

void WalkEnemy::ChangeState(std::unique_ptr<WalkEnemyStateBase>newState)
{
	if(state_)
	{
		state_->Exit(*this);
		state_ = std::move(newState);
		state_->Enter(*this);
	}
}

void WalkEnemy::Gravity()
{
	velocity_.y += 0.5f;
}

void WalkEnemy::ApplyMovement()
{
	position_ += velocity_;

	if (position_.y >= kGround)
	{
		position_.y = kGround;
		velocity_.y = 0.0f;
	}
}

void Walk::Enter(WalkEnemy& enemy)
{
	enemy.SetGraph(enemy.GetImages().walk);
}
void Walk::Update(WalkEnemy& enemy)
{
	enemy.Gravity();

	Vector2 vel = enemy.GetVelocity();
	vel.x -= kSpeed;

	if(vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	enemy.SetVelocity(vel);

	enemy.ApplyMovement();

	auto player = enemy.GetPlayer();
	Vector2 pos = enemy.GetPosition();
	Rect& rect = enemy.GetHitRect();
	rect.SetCenter(pos.x,pos.y + (kHeight/2),kWidth ,kHeight);
	Rect& playerRect = player->GetHitRect();
	//当たり判定
	if (rect.IsCollision(playerRect))
	{
		//プレイヤーが右にいるか左にいるかを判定
		float enemyToPlayer = player->GetPosition().x - enemy.GetPosition().x;
		bool isplayerOnRight = enemyToPlayer > 0 ? true : false;
		enemy.SetPlayerOnRight(isplayerOnRight);

		//エネミーの状態遷移
		enemy.ChangeState(std::make_unique<Death>());
		//プレイヤーの状態遷移
		player->ChangeState(std::make_unique<HitState>());
	}
}

void Death::Enter(WalkEnemy& enemy)
{
	enemy.SetGraph(enemy.GetImages().death);
}
void Death::Update(WalkEnemy& enemy)
{
	Vector2 vel = enemy.GetVelocity();
	bool isPlayerOnRight = enemy.GetPlayerOnRight();

	if(isPlayerOnRight)
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

void Death::Exit(WalkEnemy& enemy)
{
	//isDead_をtrueにする
	enemy.SetIsDead(true);
}

void None::Enter(WalkEnemy& enemy)
{
}
void None::Update(WalkEnemy& enemy)
{
}

