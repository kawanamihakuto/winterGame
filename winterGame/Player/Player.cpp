#include<DxLib.h>
#include "Player.h"
#include"../Scene/GameScene.h"
#include"../System/Rect.h"
#include"../System/Input.h"
#include"../System/Camera.h"
#include"PlayerState/IdleState.h"
#include"PlayerState/MoveState.h"
#include"PlayerState/JumpState.h"
#include"PlayerState/HitState.h"
#include"PlayerState/InhaleState.h"
#include"PlayerState/MouthHoldState.h"

Player::Player(PlayerImages& imgs) :
	velocity_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(true),
	images_(imgs),
	currentImage_(imgs.idle),
	hp_(5),
	rectColor_(0x0000ff),
	isGenerateInhale_(false),
	isDeleteInhale_(false),
	isRight_(true)
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
		0, 0, PlayerConstant::kWidth, PlayerConstant::kHeight,
		PlayerConstant::kSize, 0, currentImage_, true);
#ifdef _DEBUG
	//当たり判定表示
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (PlayerConstant::kHeight / 2) + camera.GetDrawOffset().y, PlayerConstant::kWidth, PlayerConstant::kHeight);
	rect_.Draw(rectColor_, false);
	//プレイヤーのHP表示
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
#endif // _DEBUG
}

void Player::ChangeState(std::unique_ptr<StateBase> newState)
{
	//プレイヤーの状態を切り替える処理
	if (state_)
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
