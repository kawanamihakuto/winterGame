#include "SunBoss.h"
#include"../BossState/BossStateBase.h"
#include"BossState/BossIdleState.h"
#include"BossState/NormalShotState.h"
#include"BossState/TripleShotState.h"
#include"BossState/DeadState.h"
#include"BossState/AppearState.h"
#include<DxLib.h>
#include"Camera.h"

namespace
{
	constexpr int kActionInterval = 60;
	constexpr float kSinFrameSpeed = 0.07f;
	constexpr float kAmplitude = 0.5f;
	constexpr double kSize = 3.0;
	constexpr double kRectSize = 1.6;

	constexpr int kDamageFlashInterval = 5;
}

SunBoss::SunBoss(Vector2 pos, int graphHandle, std::shared_ptr<Player>player,std::shared_ptr<EffectManager>effectManager) :BossBase(pos, graphHandle, player,effectManager),
actionIntervalCount_(0),
sinFrame_(0.0f),
deadCount_(0)
{
	state_ = std::make_unique<BossState::AppearState>();
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
	
	if (isDead_ == false && hp_ <= 0)
	{
		isDead_ = true;
		ChangeState(std::make_unique<BossState::DeadState>());
		return;
	}

	if (deadCount_ >= 350)
	{
		isActive_ = false;
	}

	if (!isDead_)
	{
		if (state_->GetState() != BossStateType::Appear)
		{
			if (actionIntervalCount_++ >= kActionInterval)
			{
				actionIntervalCount_ = 0;

				int nextStateNum = GetRand(2);

				if (nextStateNum == 0)
				{
					ChangeState(std::make_unique<BossState::BossIdleState>());
				}
				else if (nextStateNum)
				{
					ChangeState(std::make_unique<BossState::NormalShotState>());
				}
				else if (nextStateNum)
				{
					ChangeState(std::make_unique<BossState::TripleShotState>());
				}
			}
			position_.y += sinf(sinFrame_ += kSinFrameSpeed) * kAmplitude;
		}
	}

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
	if (isDead_)
	{
		//フェード処理
		float rate = static_cast<float>(deadCount_++) / static_cast<float>(300);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - (255 * rate));
	}
	DrawRectRotaGraph(screen.x + ShakeOffset_.x, screen.y + ShakeOffset_.y, 0, 0, srcX, srcY, kSize, 0.0, graphHandle_, true, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);

#ifdef _DEBUG
	//当たり判定表示
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX * kRectSize,
		srcY * kRectSize);
	drawRect.Draw(0xff00ff, false);

	DrawFormatString(100, 200, 0xffffff, "BossPosition : %f , %f", position_.x, position_.y);
	DrawFormatString(100, 300, 0xff00ff, "BossHp : %d", hp_);
	DrawFormatString(100, 400, 0xff00ff, "BossShakeOffset : %f,%f",ShakeOffset_.x,ShakeOffset_.y);
#endif // _DEBUG
}

void SunBoss::ChangeState(std::unique_ptr<BossState::BossStateBase> newState)
{
	if (state_ != newState)
	{
		//現在の状態のExitを呼ぶ
		state_->Exit(*this);
		//次の状態に切り替える
		state_ = std::move(newState);
		//切り替えた後の現在の状態のEnterを呼ぶ
		state_->Enter(*this);
	}
}