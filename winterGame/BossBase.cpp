#include "BossBase.h"
#include "System/Geometry.h"
BossBase::BossBase(Vector2 pos) : GameObject(pos)
{
}

BossBase::~BossBase()
{
}

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
	return CollisionLayers::kNormalPlayer;
}

void BossBase::OnCollision(GameObject& other)
{
	
}
