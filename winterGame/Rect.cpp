#include<DxLib.h>
#include "Rect.h"
#include<cassert>

Rect::Rect():
	left_(0.0f),
	top_(0.0f),
	right_(0.0f),
	bottom_(0.0f)
{
}

Rect::~Rect()
{
}

void Rect::Draw(unsigned int color, bool isFill)
{
	DrawBox(static_cast<int>(left_), static_cast<int>(top_),
		static_cast<int>(right_), static_cast<int>(bottom_),
		color, isFill);
}

void Rect::SetLT(float left, float top, float width, float height)
{
	left_ = left;
	top_ = top;
	right_ = left+width;
	bottom_ = top + height;
}

void Rect::SetCenter(float x, float y, float width, float height)
{
	left_ = x - width * 0.5f;
	top_ = y - height * 0.5f;
	right_ = x + width * 0.5f;
	bottom_ = y + height * 0.5f;
}

float Rect::GetWidth() const
{
	//左右の入れ替わりチェック
	assert(right_ >= left_);
	return right_ - left_;
}

float Rect::GetHeight() const
{
	//上下の入れ替わりチェック
	assert(bottom_ >= top_);
	return bottom_ - top_;
}

Vector2 Rect::GetCenter() const
{
	float x = (left_ + right_) * 0.5f;
	float y = (top_ + bottom_) * 0.5f;
	return Vector2();
}

bool Rect::IsCollision(const Rect& rect)
{
	//絶対に当たらないパターンを弾いていく
	if (left_ > rect.right_)return false;
	if (top_ > rect.bottom_)return false;
	if (right_ < rect.left_)return false;
	if (bottom_ < rect.top_)return false;

	//当たらないパターン以外は当たっている
	return true;
}
