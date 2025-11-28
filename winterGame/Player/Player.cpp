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
	starOrAir_(StarOrAir::star)
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
}

void Player::Draw()
{
}

void Player::Draw(Camera& camera)
{
	//プレイヤー表示
	DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		16 * static_cast<int>(graphCutNo_), 0, PlayerConstant::kWidth, PlayerConstant::kHeight,
		PlayerConstant::kSize, 0, currentImage_, true,!isRight_);
#ifdef _DEBUG
	//当たり判定表示
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (PlayerConstant::kHeight / 2) + camera.GetDrawOffset().y,
		PlayerConstant::kWidth * PlayerConstant::kRectSize, PlayerConstant::kHeight * PlayerConstant::kRectSize);
	rect_.Draw(rectColor_, false);
	
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
		//プレイヤーの状態遷移
		ChangeState(std::make_unique<PlayerState::HitState>());
	}
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

void Player::ApplyMovement()
{
	//velをposに反映
	position_ += velocity_;

	//仮の地面判定の処理
	if (position_.y >= PlayerConstant::kGround)
	{
		position_.y = PlayerConstant::kGround;
		velocity_.y = 0.0f;
		isGround_ = true;
	}
}

void Player::UpdatePhysics()
{
	//重力処理
	Gravity();
	//velocityをpositionに加える
	ApplyMovement();
}
