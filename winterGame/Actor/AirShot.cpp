#include "AirShot.h"
#include"Player.h"
#include"Camera.h"
#include"Base/EnemyBase.h"
#include"Enemy/WalkEnemy.h"
#include<DxLib.h>

//ãÛãCíeÇÃêÿÇËéÊÇËà íu
constexpr float kAirGraphCutRow = 5;
//
constexpr float kSpeed = 6.0f;
constexpr int kWidth = 32;
constexpr int kHeight = 32;
constexpr int kSrcWidth = 48;
constexpr int kSrcHeight = 32;
constexpr int kSrcSize = 16;
constexpr double kSize = 1.0;
constexpr int kCountMax = 20;

AirShot::AirShot(bool isRight,Vector2 pos, int graphHandle, std::shared_ptr<EffectManager>effectManager):Shot(isRight,pos,graphHandle,effectManager),
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

void AirShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies,Stage& stage)
{
	count_++;
	position_ += velocity_;

	if (count_ >= kCountMax)
	{
		isActive_ = false;
	}
	rect_.SetCenter(position_.x, position_.y, kWidth, kHeight);
	Rect tileRect;
	MapCollisionX(stage, tileRect);
}

void AirShot::Draw()
{
}

void AirShot::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	DrawRectRotaGraph(screen.x, screen.y,
		0, kSrcSize * kAirGraphCutRow, kSrcWidth, kSrcHeight,
		kSize, 0, graphHandle_, true, !isRight_);
#ifdef _DEBUG
	Rect drawRect = rect_;
	//ìñÇΩÇËîªíËï\é¶
	drawRect.SetCenter(screen.x, screen.y,
		kWidth, kHeight);
	drawRect.Draw(0x00aaff, false);
#endif // _DEBUG
}

