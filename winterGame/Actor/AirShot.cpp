#include "AirShot.h"
#include"../Player/Player.h"
#include"../System/Camera.h"
#include"../Base/EnemyBase.h"
#include"WalkEnemy.h"
#include<DxLib.h>

constexpr float kAirGraphCutRow = 5;
constexpr float kSpeed = 6.0f;
constexpr int kWidth = 16;
constexpr int kHeight = 16;
constexpr int kSize = 1;

AirShot::AirShot(bool isRight,Vector2 pos, int graphHandle):Shot(isRight,pos,graphHandle)
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
	position_ += velocity_;

	for (auto& enemies : enemies)
	{
		//すべてのエネミーとの当たり判定をチェック
		if (rect_.IsCollision(enemies->GetHitRect()))
		{
			//エネミーのステートを変更
			enemies->ChangeState(std::make_unique<Death>());

			isActive_ = true;
		}
	}


}

void AirShot::Draw()
{
}

void AirShot::Draw(Camera& camera)
{
	DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		0, kHeight * kAirGraphCutRow, kWidth * 3, kHeight * 2,
		kSize, 0, graphHandle_, true, !isRight_);
#ifdef _DEBUG
	//当たり判定表示
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		kWidth * 2 * kSize, kHeight* 2 * kSize);
	rect_.Draw(0x00aaff, false);
#endif // _DEBUG
}
