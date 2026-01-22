#include "BossBullet.h"
#include <DxLib.h>
#include"Camera.h"
#include"Application.h"
namespace
{
	constexpr float kSpeed = 5.0f;
	constexpr double kSize = 1.0;
	constexpr double kRectSize = 0.5;
}

BossBullet::BossBullet(Vector2 pos,Vector2 playerPos ,int graphHandle) :GameObject(pos),
graphHandle_(graphHandle),
velocity_(0,0),
isActive_(true),
playerPos_(playerPos),
vector_(0,0)
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Init()
{
	vector_ = playerPos_ - position_;
	vector_.Normalize();
	velocity_.x = vector_.x * kSpeed;
	velocity_.y = vector_.y * kSpeed;
}

void BossBullet::Update()
{
}

void BossBullet::Update(Camera& camera)
{
	auto wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);

	if (position_.x < camera.GetPosition().x - wsize.w / 2 - srcX * kSize ||
		position_.x >= camera.GetPosition().x + wsize.w / 2 + srcX * kSize ||
		position_.y < camera.GetPosition().y - wsize.h / 2 - srcY * kSize ||
		position_.y >= camera.GetPosition().y + wsize.h / 2 + srcY * kSize)
	{
		isActive_ = false;
	}
	position_ += velocity_;

	rect_.SetCenter(position_.x, position_.y, srcX* kRectSize, srcY* kRectSize);
}

void BossBullet::Draw()
{

}

void BossBullet::Draw(Camera& camera)
{
	auto screen = camera.WorldToScreen(position_);

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(screen.x, screen.y, 0, 0, srcX, srcY, kSize, 0.0, graphHandle_, true ,true);

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX * kRectSize,
		srcY * kRectSize);
	drawRect.Draw(0xff00ff, false);

	DrawFormatString(100, 250, 0xff00ff, "bossBulletPos : %f,%f", position_.x, position_.y);
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
	if (other.GetCollisionLayer() & CollisionLayers::kNormalPlayer)
	{
		isActive_ = false;
	}
}


