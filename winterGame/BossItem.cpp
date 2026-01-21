#include "BossItem.h"
#include<DxLib.h>
#include"Camera.h"

namespace
{
	constexpr double kSize = 1.5;
	constexpr float kAmplitude = -0.2f;
	constexpr float kSpeed = 0.05f;
}

BossItem::BossItem(std::shared_ptr<Player>player,Vector2 pos,int graphHandle):Item(player,ItemType::dragonFruit, pos),
graphHandle_(graphHandle),
frame_(0.0f)
{
}

BossItem::~BossItem()
{
}

void BossItem::Init()
{
	
}

void BossItem::Init(int stageNo)
{
	
}

void BossItem::Update()
{
	frame_+= kSpeed;
	position_.y += sinf(frame_) * kAmplitude;

	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	rect_.SetCenter(position_.x, position_.y, srcX * kSize, srcY * kSize);
}

void BossItem::Draw()
{

}


void BossItem::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);

	DrawRectRotaGraph(screen.x, screen.y, 0, 0, srcX, srcY, kSize, 0.0, graphHandle_, true);

#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		srcX * kSize,
		srcY * kSize);
	drawRect.Draw(0x00ffff, false);
#endif // _DEBUG
}