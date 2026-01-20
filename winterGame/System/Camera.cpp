#include "Camera.h"
#include<cmath>
#include"Player.h"
#include"Application.h"
#include"Lerp.h"

namespace
{
	constexpr float kCameraLeftLimit = 640.0f;
	constexpr float kCameraRightLimit = 6550;

	constexpr Vector2 kDefaultPosition = { 640.0f,640.0f };
}

Camera::Camera() : GameObject(kDefaultPosition),
drawOffset_({0,0}),
target_({0,0})
{
}

Camera::~Camera()
{
}
void Camera::Init()
{
}
void Camera::SetTarget(const Vector2& pos)
{
	target_ = pos;
}

void Camera::Update()
{
	Lerp lerp;
	position_.x = lerp.FLerp(position_.x, target_.x, 0.1f);

	if (position_.x <= kCameraLeftLimit)
	{
		position_.x = kCameraLeftLimit;
	}
	if (position_.x >= kCameraRightLimit)
	{
		position_.x = kCameraRightLimit;
	}
}

void Camera::Draw()
{

}

Rect Camera::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Camera::GetCollisionLayer() const
{
	return CollisionLayers::kNone;
}

CollisionLayer Camera::GetHitMask() const
{
	return CollisionLayers::kNone;
}

void Camera::OnCollision(GameObject& other)
{
}

Vector2 Camera::WorldToScreen(const Vector2& world) const
{
	auto wsize = Application::GetInstance().GetWindowSize();

	return{ world.x - position_.x + wsize.w * 0.5f,
		world.y - position_.y + wsize.h * 0.5f };
}

