#include "Inhale.h"
#include<memory>
#include<vector>
#include"Collision/Rect.h"
#include"Player.h"
#include"Base/EnemyBase.h"
#include<DxLib.h>
#include"Camera.h"
#include"WalkEnemy.h"
#include"Lerp.h"
#include"InhaleHoldState.h"
#include "Base/Shot.h"

namespace
{
	//吸い込み範囲の幅
	constexpr int kWidth = 18;
	//吸い込み範囲の高さ
	constexpr int kHeight = 18;
	//
	constexpr int kGraphWidth = 16;
	//
	constexpr int kGraphHeight = 16;
	//吸い込み範囲の拡大倍率
	constexpr int kSize = 3;
	//プレイヤーからのoffsetX
	constexpr int kOffsetX = 40;
	//アニメーションの間隔
	constexpr int kAnimFrameMax = 5;
}

Inhale::Inhale(Vector2 pos,int graphHandle,std::shared_ptr<Player>player) : GameObject(pos),
	isActive_(false),
	graphHandle_(graphHandle),
	isRight_(false),
	player_(player),
	AnimCount_(0),
	AnimNum_(0)
{
}

Inhale::~Inhale()
{
}

void Inhale::Init()
{
	isActive_ = true;
	//プレイヤーのpositionを取得
	Vector2 playerPos = player_->GetPosition();

	bool isPlayerRight = player_->GetIsRight();
	//プレイヤーが右を向いていたら
	if (isPlayerRight)
	{
		isRight_ = true;
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして右に出す
		position_.x = playerPos.x + kOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		isRight_ = false;
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = player_->GetPosition().y;

}

void Inhale::Update()
{
	//プレイヤーのpositionを取得
	Vector2 playerPos =  player_->GetPosition();
	//プレイヤーの向きを取得
	bool isPlayerRight = player_->GetIsRight();
	//プレイヤーが右を向いていたら
	if (isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして右に出す
		position_.x = playerPos.x + kOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = playerPos.y;
	if (isActive_)
	{
		//プレイヤーの吸い込み状態の継続をいったんfalseにする
		player_->SetIsInhaledHold(false);
	}
	rect_.SetCenter(position_.x, position_.y, kWidth * 2, kHeight* 2);

	if (AnimCount_++ >= kAnimFrameMax)
	{
		AnimCount_ = 0;
		AnimNum_++;
		
		if (AnimNum_ >= 6)
		{
			AnimNum_ = 0;
		}
	}
}

void Inhale::Draw()
{	
}

void Inhale::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	if (isActive_)
	{
		DrawRectRotaGraph(screen.x, screen.y - kGraphHeight / 2,
			(kGraphWidth * 3) + (kGraphWidth * AnimNum_) , 0, kGraphWidth, kGraphHeight, kSize, 0, graphHandle_,true, !isRight_);
	}
	
#ifdef _DEBUG
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth * 2, kHeight * 2);

	//当たり判定を可視化
	if (isActive_)
	{
		drawRect.Draw(0x0000ff, false);
	}
#endif // _DEBUG
}

Rect Inhale::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Inhale::GetCollisionLayer() const
{
	return CollisionLayers::kInhale;
}

CollisionLayer Inhale::GetHitMask() const
{
	return CollisionLayers::kEnemy;
}

void Inhale::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		//1体でもエネミーが吸い込み範囲にいたら
				// プレイヤーに吸い込み状態を継続させる
		player_->SetIsInhaledHold(true);
	}
}


