#include<DxLib.h>
#include "WalkEnemy.h"

namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.0f;

	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

WalkEnemy::WalkEnemy(Vector2 firstPos,int walkH) :EnemyBase(kHp, firstPos),
walkH_(walkH)
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
	state_->Draw(*this);
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

void Walk::Update(WalkEnemy& enemy)
{
	
}

void Walk::Draw(WalkEnemy& enemy)
{
	Vector2& pos = enemy.GetPosition();
	
	
}

void Death::Enter(WalkEnemy& enemy)
{
	
}
void Death::Update(WalkEnemy& enemy)
{

}
void Death::Draw(WalkEnemy& enemy)
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

