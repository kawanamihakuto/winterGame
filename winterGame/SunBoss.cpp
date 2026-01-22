#include "SunBoss.h"
#include"../BossState/BossStateBase.h"
#include"BossState/BossIdleState.h"
#include<DxLib.h>
#include"Camera.h"
SunBoss::SunBoss(Vector2 pos,int graphHandle) :BossBase(pos ,graphHandle)
{
	state_ = std::make_unique<BossState::BossIdleState>();
	state_->Enter(*this);
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

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX,
		srcY);
	drawRect.Draw(0xff00ff, false);

	DrawFormatString(100, 200, 0xffffff,"BossPosition : %f , %f",position_.x,position_.y);
#endif // _DEBUG
}

void SunBoss::ChangeState(std::unique_ptr<BossState::BossStateBase> newState)
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