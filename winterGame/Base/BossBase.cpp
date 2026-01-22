#include "BossBase.h"
#include"BossState/BossStateBase.h"
#include "System/Geometry.h"
BossBase::BossBase(Vector2 pos ,int graphHandle) : GameObject(pos),
graphHandle_(graphHandle),
hp_(100),
velocity_(0, 0)
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
	
}
