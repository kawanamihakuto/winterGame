#include "Camera.h"
#include<cmath>
#include"Player.h"
#include"Application.h"
#include"Lerp.h"

Camera::Camera() : GameObject(Vector2{320,320}),
drawOffset_({0,0})
{
}

Camera::~Camera()
{
}
void Camera::Init()
{
}
void Camera::Init(Player& player)
{
	position_ = player.GetPosition();
}

void Camera::Update()
{
}

void Camera::Update(Player& player)
{
	Lerp lerp;
	position_ = lerp.VLerp(position_, player.GetPosition(), 0.1f);

	drawOffset_.x = position_.x * -1;
	drawOffset_.y = position_.y * -1;

	auto wsize = Application::GetInstance().GetWindowSize();
	drawOffset_.x += wsize.w * 0.5f;
	drawOffset_.y += wsize.h * 0.5f;
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

