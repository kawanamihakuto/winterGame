#include "FlyEnemy.h"
#include<DxLib.h>
#include"../System/Camera.h"
#include"../System/Lerp.h"
#include"../Player/Player.h"
constexpr int kHp = 1;
constexpr int kWidth = 16;
constexpr int kHeight = 16;
constexpr int kFlyEnemyCutRow = 3;
constexpr float kSize = 3.0f;
constexpr float kRectSize = 3.0f;
constexpr float kSpeed = 1.5f;
constexpr float kMaxSpeed = 1.5f;
constexpr float kNockbackSpeed = 4.0f;
constexpr int kNockBackTimeMax = 20;

//ãzÇ¢çûÇﬁÇ∆Ç´ÇÃLerpÇÃtÇÃíl
constexpr float kInhaleLerpT = 0.05f;

FlyEnemy::FlyEnemy(Vector2 pos, int graphHandle, std::shared_ptr<Player> player):
	EnemyBase(kHp, {0,0},pos,graphHandle,player,false,0,EnemyType::fly)
{
	state_ = std::make_unique<Move>();
}

FlyEnemy::~FlyEnemy()
{
}

void FlyEnemy::Init()
{

}

void FlyEnemy::Update()
{
}

void FlyEnemy::Update(Stage& stage)
{
	state_->Update(*this);
	ApplyMovementX();
	ApplyMovementY();
	rect_.SetCenter(position_.x, position_.y,
		kWidth * kRectSize, kHeight * kRectSize);
}

void FlyEnemy::Draw()
{

}
void FlyEnemy::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	DrawRectRotaGraph(screen.x, screen.y,
		kWidth * static_cast<int>(graphCutNo_), kFlyEnemyCutRow * kHeight, kWidth, kHeight,
		kSize, 0, graphHandle_, true,isRight_);
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth * kRectSize, kHeight * kRectSize);
	drawRect.Draw(0x0000ff, false);
}

void FlyEnemy::ChangeState(std::unique_ptr<EnemyStateBase>newState)
{
	state_->Exit(*this);
	state_ = std::move(newState);
	state_->Enter(*this);
}