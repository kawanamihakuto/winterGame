#include "SunBoss.h"

SunBoss::SunBoss(Vector2 pos) :BossBase(pos)
{
}

SunBoss::~SunBoss()
{
}

void SunBoss::Init()
{
}

void SunBoss::Update()
{
}

void SunBoss::Draw()
{ 
}

void SunBoss::Draw(Camera& camera)
{
}

void SunBoss::ChangeState(std::unique_ptr<BossStateBase> newState)
{
	//ƒvƒŒƒCƒ„[‚Ìó‘Ô‚ðØ‚è‘Ö‚¦‚éˆ—
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