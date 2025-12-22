#include "AirShot.h"
#include"Player.h"
#include"Camera.h"
#include"Base/EnemyBase.h"
#include"Enemy/WalkEnemy.h"
#include<DxLib.h>

constexpr float kAirGraphCutRow = 5;
constexpr float kSpeed = 6.0f;
constexpr int kWidth = 16;
constexpr int kHeight = 16;
constexpr int kSize = 1;
constexpr int kCountMax = 20;

AirShot::AirShot(bool isRight,Vector2 pos, int graphHandle):Shot(isRight,pos,graphHandle),
count_(0)
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

AirShot::~AirShot()
{
}

void AirShot::Init()
{
}

void AirShot::Init(std::shared_ptr<Player> player)
{
}

void AirShot::Update()
{
}

void AirShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies)
{
	count_++;
	position_ += velocity_;

	if (count_ >= kCountMax)
	{
		isActive_ = false;
	}
	rect_.SetCenter(position_.x, position_.y, kWidth, kHeight);
}

void AirShot::Draw()
{
}

void AirShot::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	DrawRectRotaGraph(screen.x, screen.y,
		0, kHeight * kAirGraphCutRow, kWidth * 3, kHeight * 2,
		kSize, 0, graphHandle_, true, !isRight_);
#ifdef _DEBUG
	Rect drawRect = rect_;
	//“–‚½‚è”»’è•\Ž¦
	drawRect.SetCenter(screen.x, screen.y,
		kWidth * 2 * kSize, kHeight* 2 * kSize);
	drawRect.Draw(0x00aaff, false);
#endif // _DEBUG
}

