#include<DxLib.h>
#include "WalkEnemy.h"
#include"Collision/Rect.h"
#include"Player.h"
#include<memory>
#include"Camera.h"
#include"HitState.h"
#include"Lerp.h"
#include"Stage/Stage.h"
#include"Application.h"
namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.5f;

	constexpr int kWidth = 16;
	constexpr int kHeight = 16;
	constexpr float kSize = 3.0f;

	constexpr float kWorldSize = 16*3;
	constexpr float kRectSize = 2.0f;
	
	constexpr int kGround = 0;
	constexpr float kMaxSpeed = 1.5f;

	constexpr float kNockbackSpeed = 4.0f;
	constexpr int kNockBackTimeMax = 20;

	constexpr int kWalkEnemyGraphCutRow = 2;
	constexpr int kAnimChangeFrame = 15;
}


WalkEnemy::WalkEnemy(Vector2 pos,int graphHandle,std::shared_ptr<Player>player) :
	EnemyBase(kHp,{0,0}, pos,graphHandle,player,false,0,EnemyType::walk)

{
	state_ = std::make_unique<Move>();
	rect_.SetCenter(position_.x, position_.y,
		kWidth * kRectSize, kHeight * kRectSize);
}

WalkEnemy::~WalkEnemy()
{
}

void WalkEnemy::Init()
{
	
}

void WalkEnemy::Update()
{
}
void WalkEnemy::Update(Stage& stage,Camera& camera)
{
	auto wsize = Application::GetInstance().GetWindowSize();
	if (position_.x < camera.GetPosition().x - wsize.w / 2 - kWidth * kSize || position_.x >= camera.GetPosition().x + wsize.w / 2 + kWidth * kSize)
	{
		return;
	}
	state_->Update(*this);

	Rect tileRect;
	//重力
	Gravity();
	ApplyMovementY();
	rect_.SetCenter(position_.x, position_.y,
		kWidth * kRectSize, kHeight * kRectSize);
	MapCollisionY(stage,tileRect);

	ApplyMovementX();
	rect_.SetCenter(position_.x, position_.y,
		kWidth * kRectSize, kHeight * kRectSize);
	MapCollisionX(stage, tileRect);

	if (!isInhaled_)
	{
		if (counter_++ >= kAnimChangeFrame)
		{
			counter_ = 0;
			(graphCutNo_ += 1) %= 2;
		}
	}
}
void WalkEnemy::Draw()
{

}

void WalkEnemy::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);

	DrawRectRotaGraph(screen.x,screen.y,
		kWidth * static_cast<int>(graphCutNo_), kWalkEnemyGraphCutRow * kHeight,
		kWidth, kHeight,
		3.0,0,
		graphHandle_, true,isRight_);
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth * kRectSize , kHeight * kRectSize);
	drawRect.Draw(0x0000ff,false);
}


void WalkEnemy::ChangeState(std::unique_ptr<EnemyStateBase>newState)
{
	state_->Exit(*this);
	state_ = std::move(newState);
	state_->Enter(*this);
}

void WalkEnemy::MapCollisionX(const Stage& stage, Rect tileRect)
{
	if (stage.IsCollision(rect_, tileRect))
	{
		// 右に移動して壁に当たった場合
		if (velocity_.x > 0.0f)
		{
			//右端をタイルの左端に合わせる
			position_.x = tileRect.left_ - rect_.GetWidth() * 0.5f - 0.01f;
			isRight_ = false;
		}
		// 左に移動して壁に当たった場合
		else if (velocity_.x < 0.0f)
		{
			//左端をタイルの右端に合わせる
			position_.x = tileRect.right_ + rect_.GetWidth() * 0.5f + 0.01f;
			isRight_ = true;
		}

		// 壁に当たったのでX速度はゼロ
		velocity_.x = 0.0f;

		// 押し戻した後は必ずRectを更新
		rect_.SetCenter(
			position_.x,
			position_.y,
			PlayerConstant::kWidth * PlayerConstant::kRectSize,
			PlayerConstant::kHeight * PlayerConstant::kRectSize
		);
	}
}

void WalkEnemy::MapCollisionY(const Stage& stage, Rect tileRect)
{
	if (stage.IsCollision(rect_, tileRect))
	{
		// 落下中（床）
		if (velocity_.y > 0.0f)
		{
			//床の上に合わせる
			position_.y = tileRect.top_ - rect_.GetHeight() * 0.5f - 0.01f;

			// 落下速度を完全に止める
			velocity_.y = 0.0f;
		}
		// 上昇中（天井）
		else if (velocity_.y < 0.0f)
		{
			//天井の下に合わせる
			position_.y = tileRect.bottom_ + rect_.GetHeight() * 0.5f + 0.01f;

			// 上方向速度を止める
			velocity_.y = 0.0f;
		}
		// 押し戻し後のRect更新
		rect_.SetCenter(
			position_.x,
			position_.y,
			PlayerConstant::kWidth * PlayerConstant::kRectSize,
			PlayerConstant::kHeight * PlayerConstant::kRectSize
		);
	}
}
