#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
#include"Collision/Rect.h"
#include"Input.h"
#include"Camera.h"
#include"IdleState.h"
#include"MoveState.h"
#include"JumpState.h"
#include"HitState.h"
#include"InhaleState.h"

constexpr int kInhaledRectWidth = 8;

Player::Player(int graphHandle) :
	velocity_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(false),
	currentImage_(graphHandle),
	hp_(5),
	rectColor_(0x0000ff),
	isGenerateInhale_(false),
	isDeleteInhale_(false),
	isRight_(true),
	isInhaleHold_(false),
	mouthState_(MouthState::empty),
	graphCutNo_(PlayerGraphCutNo::mouthClosed),
	isSpit_(false),
	starOrAir_(StarOrAir::star),
	isGanarateInhaledRect_(false),
	isDeleteInhaledRect_(false),
	invincinleFrame_(0),
	nockBackTime_(0)
{
	state_ = std::make_unique<PlayerState::IdleState>();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
}
void Player::Update(Input& input)
{
	isGenerateInhale_ = false;
	isDeleteInhale_ = false;

	//現在の状態のUpdateを呼び出す
	state_->Update(*this, input);

	rect_.SetCenter(
		position_.x,
		position_.y,
		PlayerConstant::kWidth,
		PlayerConstant::kHeight
	);
}

void Player::Draw()
{
}

void Player::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	
	int srcX = PlayerConstant::kWidth * static_cast<int>(graphCutNo_);
	int srcY = 0;

	//プレイヤー表示
	DrawRectRotaGraph(
		(int)screen.x,
		(int)screen.y,
		srcX, srcY,
		16, 16,
		3.0,
		0.0,
		currentImage_,
		TRUE,
		!isRight_
	);
#ifdef _DEBUG
	//当たり判定表示
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		PlayerConstant::kWidth, PlayerConstant::kHeight);
	drawRect.Draw(rectColor_, false);

	//プレイヤーのHP表示
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
#endif // _DEBUG
}

Rect Player::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Player::GetCollisionLayer() const
{
	return CollisionLayers::kNormalPlayer;
}

CollisionLayer Player::GetHitMask() const
{
	return CollisionLayers::kEnemy;
}

void Player::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		hp_ -= 1;

		if (position_.x - other.GetPosition().x <= 0)
		{
			velocity_.x = -PlayerConstant::kNockbackSpeed;
		}
		else
		{
			velocity_.x = PlayerConstant::kNockbackSpeed;
		}
		nockBackTime_ = 0;
		//プレイヤーの状態遷移
		ChangeState(std::make_unique<PlayerState::HitState>());
	}
}

void Player::OnCollisionTile(const Rect& tileRect)
{
	//Y方向の衝突判定
	if (collisionAxis_ == CollisionAxis::y)
	{
		//落下中
		if (velocity_.y > 0)
		{
			position_.y = tileRect.top_ - rect_.GetHeight() * 0.5f;
			velocity_.y = 0.0f;
			isGround_ = true;
		}
		//上昇中
		else if (velocity_.y < 0)
		{
			position_.y = tileRect.bottom_ + rect_.GetHeight() * 0.5f;
			velocity_.y = 0.0f;
		}
	}

}

bool Player::IsNockBackEnd()
{ 
	if (nockBackTime_ >= PlayerConstant::kNockBackTimeMax)
	{
		nockBackTime_ = 0;
		return true;
	}	 
	return false;
}

void Player::SetCollisionAxis(CollisionAxis collisionAxis)
{
	collisionAxis_ = collisionAxis;
}

void Player::ChangeState(std::unique_ptr<StateBase> newState)
{
	//プレイヤーの状態を切り替える処理
	if (state_ != newState)
	{
		//現在の状態のExitを呼ぶ
		state_->Exit(*this);
		//次の状態に切り替える
		state_ = std::move(newState);
		//切り替えた後の現在の状態のEnterを呼ぶ
		state_->Enter(*this);
	}
}

void Player::Gravity()
{
	//重力分下方向に力を加える
	velocity_.y += PlayerConstant::kGravity;
}

void Player::ApplyMovementX()
{
	position_.x += velocity_.x;
}

void Player::ApplyMovementY()
{
	position_.y += velocity_.y;
}
