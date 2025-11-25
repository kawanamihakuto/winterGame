#include "StarShot.h"
#include"../Player/Player.h"
#include"../System/Camera.h"
#include"../Base/EnemyBase.h"
#include"WalkEnemy.h"
#include<DxLib.h>
constexpr float kSpeed = 3.0f;
constexpr int kStarGraphCutRow = 1;
constexpr int kWidth = 16;
constexpr int kHeight = 16;
constexpr int kSize = 2;

StarShot::StarShot(bool isRight,Vector2 pos, int graphHandle) :Shot(isRight,pos,graphHandle)
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

void StarShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies)
{
	position_ += velocity_;
	
	for (auto& enemies : enemies)
	{
		//すべてのエネミーとの当たり判定をチェック
		if (rect_.IsCollision(enemies->GetHitRect()))
		{
			//1体でもエネミーが吸い込み範囲にいたら
			// プレイヤーに吸い込み状態を継続させる
			player->SetIsInhaledHold(true);
			//エネミーのステートを変更
			enemies->ChangeState(std::make_unique<Death>());

			isActive_ = true;
		}
	}
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
	//当たり判定表示
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		kWidth * kSize, kHeight * kSize);
	rect_.Draw(0x00aaff, false);
#endif // _DEBUG
}

