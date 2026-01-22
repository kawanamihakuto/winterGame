#include "StarShot.h"
#include"Player.h"
#include"Camera.h"
#include"Base/EnemyBase.h"
#include"WalkEnemy.h"
#include<DxLib.h>
constexpr float kSpeed = 6.0f;
constexpr int kStarGraphCutRow = 1;
constexpr int kWidth = 16;
constexpr int kHeight = 16;
constexpr int kSize = 2;

StarShot::StarShot(bool isRight,Vector2 pos, int graphHandle, std::shared_ptr<EffectManager>effectManager) :Shot(isRight,pos,graphHandle,effectManager)
{
	if (isRight)
	{
		isRight_ = true;
		velocity_.x = kSpeed;
	}
	else
	{
		isRight_ = false;
		velocity_.x = -kSpeed;
	}
}

StarShot::~StarShot()
{
}

void StarShot::Init()
{
}

void StarShot::Init(std::shared_ptr<Player> player)
{
	
}

void StarShot::Update()
{
}

void StarShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies,Stage& stage)
{
	position_ += velocity_;
	rect_.SetCenter(position_.x, position_.y, kWidth, kHeight);
	Rect tileRect;
	MapCollisionX(stage, tileRect);
}

void StarShot::Draw()
{
}

void StarShot::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	DrawRectRotaGraph(screen.x,screen.y,
		0, kHeight * kStarGraphCutRow,kWidth,kHeight,
		kSize,0,graphHandle_,true,!isRight_);
#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth * kSize, kHeight * kSize);
	drawRect.Draw(0x00aaff, false);
#endif // _DEBUG
}

