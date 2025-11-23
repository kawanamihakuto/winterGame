#include "StarShot.h"
#include"../Player/Player.h"
#include"../System/Camera.h"
#include<DxLib.h>
constexpr float kSpeed = 3.0f;
constexpr int kStarGraphCutRow = 1;
constexpr int kWidth = 32;
constexpr int kHeight = 32;
constexpr int kSize = 2;

StarShot::StarShot(Vector2 pos, int graphHandle) :Shot(pos,graphHandle)
{

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

void StarShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies)
{
	if (player->GetIsRight())
	{
		isRight_ = true;
		velocity_.x = kSpeed;
	}
	else
	{
		isRight_ = false;
		velocity_.x = -kSpeed;
	}
	position_ += velocity_;
}

void StarShot::Draw()
{
}

void StarShot::Draw(Camera& camera)
{
	DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x,position_.y +camera.GetDrawOffset().y,
		0, kHeight * kStarGraphCutRow,kWidth,kHeight,
		kSize,0,graphHandle_,true,!isRight_);
#ifdef _DEBUG
	//“–‚½‚è”»’è•\Ž¦
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		kWidth * kSize, kHeight * kSize);
	rect_.Draw(0x00aaff, false);
#endif // _DEBUG
}

