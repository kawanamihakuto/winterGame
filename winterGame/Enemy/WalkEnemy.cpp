#include<DxLib.h>
#include "WalkEnemy.h"
#include"Collision/Rect.h"
#include"Player.h"
#include<memory>
#include"Camera.h"
#include"HitState.h"
#include"Lerp.h"
namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.5f;

	constexpr int kWidth = 16;
	constexpr int kHeight = 16;
	constexpr float kSize = 3.0f;
	constexpr float kRectSize = 2.0f;
	constexpr float kGravity = 0.5f;
	constexpr int kGround = 400;
	constexpr float kMaxSpeed = 1.5f;

	constexpr float kNockbackSpeed = 4.0f;
	constexpr int kNockBackTimeMax = 20;

	constexpr int kWalkEnemyGraphCutRow = 2;
	//ãzÇ¢çûÇﬁÇ∆Ç´ÇÃLerpÇÃtÇÃíl
	constexpr float kInhaleLerpT = 0.05f;
}


WalkEnemy::WalkEnemy(Vector2 pos,int graphHandle,std::shared_ptr<Player>player) :
	EnemyBase(kHp,{0,0}, pos,graphHandle,player,false,0)

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

}

void WalkEnemy::Draw(Camera& camera)
{
	DrawRectRotaGraph(position_.x +camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		kWidth * static_cast<int>(graphCutNo_), kWalkEnemyGraphCutRow * kHeight, kWidth, kHeight,
		kSize,0, graphHandle_, true);
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight * 0.5f)+camera.GetDrawOffset().y,
		kWidth * kRectSize , kHeight * kRectSize);
	rect_.Draw(0x0000ff,false);
}


void WalkEnemy::ChangeState(std::unique_ptr<EnemyStateBase>newState)
{
	state_->Exit(*this);
	state_ = std::move(newState);
	state_->Enter(*this);
}

void Walk::Enter(EnemyBase& enemy)
{
}
void Walk::Update(EnemyBase& enemy)
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
}

void Walk::Exit(EnemyBase& enemy)
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

void Death::Exit(EnemyBase& enemy)
{
}

void None::Enter(EnemyBase& enemy)
{
	//isDead_ÇtrueÇ…Ç∑ÇÈ
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
	//ãzÇ¢çûÇ‹ÇÍÇƒÇ¢ÇÈìGÇÃãììÆÇLerpÇ≈é¿ëï
	enemy.SetPosition(lerp.VLerp(enemy.GetPosition(), player->GetPosition(), kInhaleLerpT));
	enemy.Gravity();
	enemy.ApplyMovement();
}
void Inhaled::Exit(EnemyBase& enemy)
{
	
}

