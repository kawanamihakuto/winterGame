#include<DxLib.h>
#include "Player.h"
#include"../Scene/GameScene.h"
#include"../System/Rect.h"
#include"../System/Input.h"
#include"../System/Camera.h"
namespace
{
	
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	constexpr float kSize = 2.0f;

	constexpr int kGround = 400;

	constexpr float kMoveSpeed = 1.0f;
	constexpr float kGravity = 0.4f;
	constexpr float kJumpPower = 8.0f;

	constexpr float kMaxSpeed = 3.0f;
	constexpr float kFriction = 0.90f;
}



Player::Player(PlayerImages& imgs) :
	velocity_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(true),
	images_(imgs),
	currentImage_(imgs.idle),
	hp_(5),
	rectColor_(0x0000ff),
	isGenerateInhale_(false),
	isDeleteInhale_(false)
{
	state_ = std::make_unique<IdleState>();
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
	state_->Update(*this, input);
}

void Player::Draw()
{
	
}

void Player::Draw(Camera& camera)
{
	DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		0, 0, kWidth, kHeight,
		kSize, 0, currentImage_, true);
	
	//当たり判定用
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight / 2)+camera.GetDrawOffset().y, kWidth, kHeight);
	rect_.Draw(rectColor_, false);
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
}

void Player::ChangeState(std::unique_ptr<PlayerStateBase> newState)
{
	// Stateパターンの状態遷移処理
	if (state_)
	{
		state_->Exit(*this);
		state_ = std::move(newState);
		state_->Enter(*this);
	}
}

void Player::Gravity()
{
	velocity_.y += kGravity;
}

void Player::ApplyMovement()
{
	position_ += velocity_;

	if (position_.y >= kGround)
	{
		position_.y = kGround;
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

void IdleState::Enter(Player& player)
{
	//画像をIdleに変更 / velocityを0にする
	player.SetGraph(player.GetImages().idle);
	Vector2 vel = player.GetVelocity();
	vel.x = 0.0f;
	player.SetVelocity(vel);
}

void IdleState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//左右どちらかの入力があったらMoveへ遷移
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//ジャンプ入力があったらJumpへ遷移
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
	}
	else if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}
	
	player.UpdatePhysics();
}


void MoveState::Enter(Player& player)
{
	//画像をMoveに変更
	player.SetGraph(player.GetImages().move);
}

void MoveState::Update(Player& player, Input& input)
{
	Vector2 vel = player.GetVelocity();
	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		vel.x -= kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		vel.x += kMoveSpeed;
	}
	//ジャンプ入力があったらJumpへ遷移
	if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
		return;
	}
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

	//摩擦処理
	vel.x *= kFriction;

	//速度制限
	if (vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	player.SetVelocity(vel);

	//速度がほぼ0になったらIdleへ遷移
	if (vel.x <= 0.1f&&vel.x >= -0.1)
	{
		player.ChangeState(std::make_unique<IdleState>());
	}

	player.UpdatePhysics();
}


void JumpState::Enter(Player& player)
{
	//画像をJumpに変更 / 上方向へ速度を与える
	player.SetGraph(player.GetImages().jump);
	Vector2 vel = player.GetVelocity();
	vel.y = -kJumpPower;
	player.SetVelocity(vel);
}

void JumpState::Update(Player& player, Input& input)
{
	Vector2 vel = player.GetVelocity();

	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		vel.x -= kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		vel.x += kMoveSpeed;
	}

	//速度制限
	if (vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	player.SetVelocity(vel);
	player.UpdatePhysics();
	
	auto pos = player.GetPosition();
	//地面に着地したらIdleかMoveへ遷移
	if (pos.y >= kGround)
	{
		if (input.IsPressed("left") || input.IsPressed("right"))
		{
			player.ChangeState(std::make_unique<MoveState>());
		}
		else
		{
			player.ChangeState(std::make_unique<IdleState>());
		}
	}
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

}

void HitState::Enter(Player& player)
{
	//hpを減らす処理
	int hp = player.GetHp();
	hp-=1;
	player.SetHp(hp);

	int rectColor = 0xff0000;
	player.SetRectColor(rectColor);
}
void HitState::Update(Player& player,Input& input)
{
	if (input.IsPressed("left") || input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	else
	{
		player.ChangeState(std::make_unique<IdleState>());
	}
	
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}
	player.UpdatePhysics();
}
void HitState::Exit(Player& player)
{
	int rectColor = 0x0000ff;
	player.SetRectColor(rectColor);
}

void InhaleState::Enter(Player& player)
{
	//画像をInhaleに変更
	player.SetGraph(player.GetImages().inhale);
	player.SetGenerateInhale(true);
}

void InhaleState::Update(Player& player, Input& input)
{
	if (!input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<IdleState>());
	}
}

void InhaleState::Exit(Player& player)
{
	player.SetDeleteInhale(true);
}