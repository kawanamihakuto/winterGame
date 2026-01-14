#include "Door.h"
#include"Camera.h"
#include<DxLib.h>
namespace
{
	constexpr int kWidth = 16;
	constexpr int kHeight = 32;

	constexpr int kSize = 3;
}


Door::Door(int graphHandle) :GameObject({6800,720}),
graphHandle_(graphHandle)
{
	rect_.SetCenter(position_.x, position_.y, kWidth * kSize, kHeight * kSize);
}

Door::~Door()
{
}

void Door::Init()
{
}

void Door::Update()
{
	rect_.SetCenter(position_.x, position_.y, kWidth * kSize, kHeight * kSize);
}

void Door::Draw()
{
}

void Door::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);

	DrawRectRotaGraph(screen.x,screen.y,62,114,kWidth + 4,kHeight,kSize,0.0,graphHandle_,true);

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth*kSize,
		kHeight*kSize);
	drawRect.Draw(0x00ffff, false);

#endif // _DEBUG
}

Rect Door::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Door::GetCollisionLayer() const
{
	return CollisionLayers::kDoor;
}

CollisionLayer Door::GetHitMask() const
{
	return CollisionLayers::kNormalPlayer;
}

void Door::OnCollision(GameObject& other)
{
}
