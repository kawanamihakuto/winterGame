#include "SunBoss.h"
#include"../BossState/BossStateBase.h"
#include"BossState/BossIdleState.h"
#include<DxLib.h>
#include"Camera.h"
SunBoss::SunBoss(Vector2 pos,int graphHandle) :BossBase(pos),
graphHandle_(graphHandle)
{
	state_ = std::make_unique<BossIdleState>();
}

SunBoss::~SunBoss()
{
}

void SunBoss::Init()
{
}

void SunBoss::Init(int stageNo)
{
}

void SunBoss::Update()
{
	state_->Update(*this);

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	rect_.SetCenter(position_.x, position_.y, srcX, srcY);
}

void SunBoss::Draw()
{ 
}

void SunBoss::Draw(Camera& camera)
{
	auto screen = camera.WorldToScreen(position_);
	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(screen.x,screen.y, 0,0,srcX, srcY,1.0,0.0,graphHandle_,true,true);
}

void SunBoss::ChangeState(std::unique_ptr<BossStateBase> newState)
{
	if (state_ != newState)
	{
		//Œ»Ý‚Ìó‘Ô‚ÌExit‚ðŒÄ‚Ô
		state_->Exit(*this);
		//ŽŸ‚Ìó‘Ô‚ÉØ‚è‘Ö‚¦‚é
		state_ = std::move(newState);
		//Ø‚è‘Ö‚¦‚½Œã‚ÌŒ»Ý‚Ìó‘Ô‚ÌEnter‚ðŒÄ‚Ô
		state_->Enter(*this);
	}
}