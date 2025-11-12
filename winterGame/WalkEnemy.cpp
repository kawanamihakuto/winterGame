#include<DxLib.h>
#include "WalkEnemy.h"
#include"Rect.h"
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
}

WalkEnemy::WalkEnemy(Vector2 pos,WalkEnemyImages& imgs) :EnemyBase(kHp,{0,0}, pos),
images_(imgs),
currentImage_(images_.walk)
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
	Vector2& pos = GetPosition();
	DrawRectRotaGraph(pos.x, pos.y, 0, 0, kWidth, kHeight, kSize,0, currentImage_, true);
	Rect& rect = GetHitRect();
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

	Vector2 pos = enemy.GetPosition();
	Rect& rect = enemy.GetHitRect();
	rect.SetCenter(pos.x,pos.y + (kHeight/2),kWidth ,kHeight);
}

void Death::Enter(WalkEnemy& enemy)
{
	
}
void Death::Update(WalkEnemy& enemy)
{

}

void Death::Exit(WalkEnemy& enemy)
{

}

void None::Enter(WalkEnemy& enemy)
{
}
void None::Update(WalkEnemy& enemy)
{
}

