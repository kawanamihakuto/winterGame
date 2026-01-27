#include "PlayerInhaledRect.h"
#include"../Player/Player.h"
#include"../System/Camera.h"
#include<DxLib.h>
constexpr int kInhakedRectOffsetX = 32/2;
constexpr int kWidth = 8;
constexpr int kHeight = 48;
PlayerInhaledRect::PlayerInhaledRect(Vector2 pos, std::shared_ptr<Player> player):
	GameObject(pos),
	isActive_(false),
	isRight_(false),
	player_(player)
{
}

PlayerInhaledRect::~PlayerInhaledRect()
{
}

void PlayerInhaledRect::Init()
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
		position_.x = playerPos.x + kInhakedRectOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		isRight_ = false;
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kInhakedRectOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = player_->GetPosition().y;
}

void PlayerInhaledRect::Update()
{
	//プレイヤーのpositionを取得
	Vector2 playerPos = player_->GetPosition();
	//プレイヤーの向きを取得
	bool isPlayerRight = player_->GetIsRight();
	//プレイヤーが右を向いていたら
	if (isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして右に出す
		position_.x = playerPos.x + kInhakedRectOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kInhakedRectOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = playerPos.y;

	rect_.SetCenter(position_.x, position_.y, kWidth, kHeight);
}


void PlayerInhaledRect::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		kWidth, kHeight);
#ifdef _DEBUG
	//当たり判定を可視化
	if (isActive_)
	{
		drawRect.Draw(0xff00ff, false);
	}
#endif // _DEBUG
}


Rect PlayerInhaledRect::GetColliderRect() const
{
	return rect_;
}

CollisionLayer PlayerInhaledRect::GetCollisionLayer() const
{
	return CollisionLayers::kInhaledPlayer;
}

CollisionLayer PlayerInhaledRect::GetHitMask() const
{
	return CollisionLayers::kEnemy;
}

void PlayerInhaledRect::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		
	}
}

void PlayerInhaledRect::Draw()
{
}
