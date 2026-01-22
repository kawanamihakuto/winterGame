#include "BossBullet.h"
#include <DxLib.h>
#include"Camera.h"

BossBullet::BossBullet(Vector2 pos, int graphHandle) :GameObject(pos),
graphHandle_(graphHandle),
velocity_(0,0)
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Init()
{
	velocity_.x = -5.0f;
}

void BossBullet::Update()
{
	position_ += velocity_;

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	rect_.SetCenter(position_.x, position_.y, srcX, srcY);
}

void BossBullet::Draw()
{

}

void BossBullet::Draw(Camera& camera)
{
	auto screen = camera.WorldToScreen(position_);

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(screen.x, screen.y, 0, 0, srcX, srcY, 1.0, 0.0, graphHandle_, true);

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX,
		srcY);
	drawRect.Draw(0xff00ff, false);
#endif // _DEBUG
}

Rect BossBullet::GetColliderRect() const
{
	return rect_;
}

CollisionLayer BossBullet::GetCollisionLayer() const
{
	return CollisionLayers::kBossAttack;
}

CollisionLayer BossBullet::GetHitMask() const
{
	return CollisionLayers::kNormalPlayer;
}

void BossBullet::OnCollision(GameObject& other)
{
	
}


