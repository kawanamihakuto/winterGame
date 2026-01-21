#include "Item.h"
#include"Application.h"
#include"System/Geometry.h"
#include"Player/Player.h"

Item::Item(std::shared_ptr<Player>player, ItemType itemType, Vector2 pos) : GameObject(pos),
player_(player),
itemType_(itemType),
isActive_(true)
{
}

Item::~Item()
{
}

Rect Item::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Item::GetCollisionLayer() const
{
	return CollisionLayers::kItem;
}

CollisionLayer Item::GetHitMask() const
{
	return CollisionLayers::kNormalPlayer;
}

void Item::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kNormalPlayer)
	{
		player_->OnGetItem(GetItemType());
		isActive_ = false;
	}
}
