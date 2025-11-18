#include "Camera.h"
#include<cmath>
#include"../Actor/Player.h"
#include"../Application.h"

Vector2 Camera::VLerp(const Vector2& stert, const Vector2& end, float t)
{
	Vector2 ret;
	ret.x = std::lerp(stert.x, end.x, t);
	ret.y = std::lerp(stert.y, end.y, t);
	return ret;
}

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
	position_ = VLerp(position_, player.GetPosition(), 0.1);
	
	drawOffset_.x = position_.x * -1;
	drawOffset_.y = position_.y * -1;

	auto wsize = Application::GetInstance().GetWindowSize();
	drawOffset_.x += wsize.w * 0.5f;
	drawOffset_.y += wsize.h * 0.5f;
}

void Camera::Draw()
{

}

