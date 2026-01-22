#include "Camera.h"
#include<cmath>
#include"Player.h"
#include"Application.h"
#include"Lerp.h"

namespace
{
	//ステージ1のカメラ制限
	constexpr float kCameraLeftLimit = 640.0f;
	constexpr float kCameraRightLimit = 6550;

	//ステージ2のカメラ制限
	constexpr float kCameraTopLimit = 640.0f;

	constexpr Vector2 kStage1DefaultPosition = { 640.0f,640.0f };
	constexpr Vector2 kStage2DefaultPosition = { 640.0f,607.7f };
	constexpr Vector2 kStage3DefaultPosition = { 640.0f,640.0f };
}

Camera::Camera() : GameObject(kStage1DefaultPosition),
drawOffset_({0,0}),
target_({0,0}),
stageNo_(1)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
}
void Camera::Init(int stageNo)
{
	stageNo_ = stageNo;
	switch (stageNo_)
	{
	case 1:
		position_ = kStage1DefaultPosition;
		break;
	case 2:
		position_ = kStage2DefaultPosition;
		break;
	case 3:
		position_ = kStage3DefaultPosition;
		break;
	}
}
void Camera::SetTarget(const Vector2& pos)
{
	target_ = pos;
}

void Camera::Update()
{
	Lerp lerp;
	switch (stageNo_)
	{
	case 1:
		position_.x = lerp.FLerp(position_.x, target_.x, 0.1f);

		if (position_.x <= kCameraLeftLimit)
		{
			position_.x = kCameraLeftLimit;
		}
		if (position_.x >= kCameraRightLimit)
		{
			position_.x = kCameraRightLimit;
		}
		break;
	case 2:
		position_.y = lerp.FLerp(position_.y, target_.y, 0.1f);

		if (position_.y <= kStage2DefaultPosition.y)
		{
			position_.y = kStage2DefaultPosition.y;
		}
		break;
	case 3:
		position_.x = lerp.FLerp(position_.x, target_.x, 0.1f);

		if (position_.x <= kCameraLeftLimit)
		{
			position_.x = kCameraLeftLimit;
		}
		if (position_.x >= kCameraRightLimit)
		{
			position_.x = kCameraRightLimit;
		}
		break;
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

