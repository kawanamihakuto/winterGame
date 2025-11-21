#include "Shot.h"
#include<memory>
#include<vector>
#include"../System/Rect.h"
#include"../Player/Player.h"
#include"../Base/EnemyBase.h"
#include<DxLib.h>
#include"../System/Camera.h"
#include"WalkEnemy.h"
#include"../System/Lerp.h"
#include"../Player/PlayerState/InhaleHoldState.h"

constexpr float kSpeed = 3.0f;
constexpr float kStarGraphCutRow = 1;
constexpr float kAirGraphCutRow = 5;
constexpr int kWidth = 32;
constexpr int kHeight = 32;

Shot::Shot(Vector2 pos,int graphHandle):
	GameObject(pos),
	velocity_({0.0f,0.0f}),
	graphHandle_(graphHandle),
	isRight_(false),
	GraphCutNo_(0),
	isActive_(false)
{
}

Shot::~Shot()
{
}

void Shot::Init()
{
}

void Shot::Init(std::shared_ptr<Player> player)
{
	if (player->GetIsRight())
	{
		isRight_ = true;
	}
	else
	{
		isRight_ = false;
	}

	switch (player->GetMouthState())
	{
	case MouthState::HoldingEnemy:
		GraphCutNo_ = kStarGraphCutRow;
		break;
	case MouthState::HoldingAir:
		GraphCutNo_ = kAirGraphCutRow;
		break;
	}
}

void Shot::Update()
{
	
}

void Shot::Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies)
{
	if (isActive_)
	{
		position_ += velocity_;
	}
}

void Shot::Draw()
{
}

void Shot::Draw(Camera& camera)
{ 
	if (isActive_)
	{
		DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
			16 * GraphCutNo_, 0, 32, 32, 0.5f, 0, graphHandle_, true, !isRight_);
	}
#ifdef _DEBUG
	//“–‚½‚è”»’è‚ð‰ÂŽ‹‰»
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight * 0.5f) + camera.GetDrawOffset().y, kWidth, kHeight);
	rect_.Draw(0x00ffff, false);
#endif // _DEBUG
}
