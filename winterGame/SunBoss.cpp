#include "SunBoss.h"
#include"../BossState/BossStateBase.h"
#include"BossState/BossIdleState.h"
#include"BossState/NormalShotState.h"
#include<DxLib.h>
#include"Camera.h"

namespace
{
	constexpr int kActionInterval = 180;
	constexpr float kSinFrameSpeed = 0.07f;
	constexpr float kAmplitude = 0.5f;
	constexpr double kSize = 3.0;
	constexpr double kRectSize = 1.6;

	constexpr int kDamageFlashInterval = 5;
}

SunBoss::SunBoss(Vector2 pos,int graphHandle,std::shared_ptr<Player>player) :BossBase(pos ,graphHandle,player),
actionIntervalCount_(0),
sinFrame_(0.0f)
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
	if (damageTimer_-- > 0)
	{
	}

	if (actionIntervalCount_++ >= kActionInterval)
	{
		actionIntervalCount_ = 0;

		if (state_->GetState() == BossStateType::Idle)
		{
			ChangeState(std::make_unique<BossState::NormalShotState>());
		}
		else if (state_->GetState() == BossStateType::NormalShot)
		{
			ChangeState(std::make_unique<BossState::BossIdleState>());
		}
	}

	position_.y += sinf(sinFrame_+= kSinFrameSpeed) * kAmplitude;

	state_->Update(*this);

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	rect_.SetCenter(position_.x, position_.y, srcX * kRectSize, srcY * kRectSize);
}

void SunBoss::Draw()
{ 
}

void SunBoss::Draw(Camera& camera)
{
	auto screen = camera.WorldToScreen(position_);
	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);

	if ((damageTimer_ / kDamageFlashInterval) % 2 == 1)
	{
		SetDrawBright(255, 128, 128);
	}
	DrawRectRotaGraph(screen.x,screen.y, 0,0,srcX, srcY, kSize,0.0,graphHandle_,true,true);

	SetDrawBright(255, 255, 255);

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX * kRectSize,
		srcY * kRectSize);
	drawRect.Draw(0xff00ff, false);

	DrawFormatString(100, 200, 0xffffff,"BossPosition : %f , %f",position_.x,position_.y);
	DrawFormatString(100, 300, 0xff00ff, "BossHp : %d", hp_);
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