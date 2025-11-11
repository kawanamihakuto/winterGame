#include<DxLib.h>
#include "WalkEnemy.h"

namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.0f;

	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
}

WalkEnemy::WalkEnemy(Vector2 pos,WalkEnemyImages& imgs) :EnemyBase(kHp, pos),
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
	DrawRectGraph(pos.x, pos.y, 0, 0, kWidth, kHeight, currentImage_, true);
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

