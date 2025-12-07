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
	constexpr float kWorldSize = 16*3;
	constexpr float kRectSize = 2.0f;
	
	constexpr int kGround = 0;
	constexpr float kMaxSpeed = 1.5f;

	constexpr float kNockbackSpeed = 4.0f;
	constexpr int kNockBackTimeMax = 20;

	constexpr int kWalkEnemyGraphCutRow = 2;

}


WalkEnemy::WalkEnemy(Vector2 pos,int graphHandle,std::shared_ptr<Player>player) :
	EnemyBase(kHp,{0,0}, pos,graphHandle,player,false,0,EnemyType::walk)

{
	state_ = std::make_unique<Move>();
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
	Vector2 screen = camera.WorldToScreen(position_);

	DrawRectRotaGraph(screen.x,screen.y,
		kWidth * static_cast<int>(graphCutNo_), kWalkEnemyGraphCutRow * kHeight,
		kWidth, kHeight,
		3.0,0,
		graphHandle_, true,isRight_);

	rect_.SetCenter(screen.x, screen.y,
		kWidth * kRectSize , kHeight * kRectSize);
	rect_.Draw(0x0000ff,false);
	rect_.Draw(0x0000ff,false);
}


void WalkEnemy::ChangeState(std::unique_ptr<EnemyStateBase>newState)
{
	state_->Exit(*this);
	state_ = std::move(newState);
	state_->Enter(*this);
}

