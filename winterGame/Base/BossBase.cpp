#include "BossBase.h"
#include"BossState/BossStateBase.h"
#include "System/Geometry.h"

namespace
{
	constexpr int kDefaultMaxHP = 30;
	constexpr int kDamageTimerMax = 20;
}

BossBase::BossBase(Vector2 pos ,int graphHandle,std::shared_ptr<Player>player,std::shared_ptr<EffectManager>effectManager) : GameObject(pos),
graphHandle_(graphHandle),
hp_(kDefaultMaxHP),
velocity_(0, 0),
isShot_(false),
player_(player),
isActive_(true),
damageTimer_(),
requestCameraShake_(false),
isDead_(false),
requestSceneModeChange_(false),
ShakeOffset_(0,0),
effectManager_(effectManager)
{
}

BossBase::~BossBase() = default;

Rect BossBase::GetColliderRect() const
{
	return rect_;
}

CollisionLayer BossBase::GetCollisionLayer() const
{
	return CollisionLayers::kBoss;
}

CollisionLayer BossBase::GetHitMask() const
{
	return CollisionLayers::kNormalPlayer|
		CollisionLayers::kAttack;
}

void BossBase::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kAttack)
	{
		OnDamage();
	}
}

int BossBase::GetMaxHP()
{
	return kDefaultMaxHP;
}

void BossBase::OnDamage()
{
	damageTimer_ = kDamageTimerMax;
	hp_--;
}
