#include<DxLib.h>
#include "WalkEnemy.h"

namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.0f;
}

WalkEnemy::WalkEnemy(Vector2& firstPos) :EnemyBase(kHp, firstPos)
{
	
}

WalkEnemy::~WalkEnemy()
{
}

void WalkEnemy::Init()
{
	
}

void WalkEnemy::Update()
{

}

void WalkEnemy::Draw()
{

}

void WalkEnemy::ChangeState(std::unique_ptr<StateBase>newState)
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

