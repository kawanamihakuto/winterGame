#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
#include"Rect.h"
#include"Input.h"
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
	currentImage_(imgs.idle)
{
	state_ = std::make_unique<Idle>();
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
	Vector2& pos = GetPosition();
	DrawRectRotaGraph(pos.x, pos.y,0, 0, kWidth, kHeight, kSize,0,currentImage_, true);
	Rect& rect = GetHitRect();
	rect.Draw(0x0000ff,false);
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

void Idle::Enter(Player& player)
{
	//画像をIdleに変更 / velocityを0にする
	player.SetGraph(player.GetImages().idle);
	Vector2 vel = player.GetVelocity();
	vel.x = 0.0f;
	player.SetVelocity(vel);
}

void Idle::Update(Player& player, Input& input)
{
	//重力処理
	player.Gravity();

	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//左右どちらかの入力があったらMoveへ遷移
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<Move>());
	}
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<Move>());
	}
	//ジャンプ入力があったらJumpへ遷移
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<Jump>());
	}
	
	player.ApplyMovement();
	Vector2& pos = player.GetPosition();
	Rect& rect = player.GetHitRect();
	rect.SetCenter(pos.x,pos.y +(kHeight/2), kWidth, kHeight);
}


void Move::Enter(Player& player)
{
	//画像をMoveに変更
	player.SetGraph(player.GetImages().move);
}

void Move::Update(Player& player, Input& input)
{
	//重力処理
	player.Gravity();

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
		player.ChangeState(std::make_unique<Jump>());
		return;
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
		player.ChangeState(std::make_unique<Idle>());
	}

	player.ApplyMovement();
	Vector2& pos = player.GetPosition();
	Rect& rect = player.GetHitRect();
	rect.SetCenter(pos.x, pos.y + (kHeight / 2), kWidth, kHeight);

}


void Jump::Enter(Player& player)
{
	//画像をJumpに変更 / 上方向へ速度を与える
	player.SetGraph(player.GetImages().jump);
	Vector2 vel = player.GetVelocity();
	vel.y = -kJumpPower;
	player.SetVelocity(vel);
}

void Jump::Update(Player& player, Input& input)
{
	//重力処理
	player.Gravity();

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
	player.ApplyMovement();
	Vector2 pos= player.GetPosition();
	Rect& rect = player.GetHitRect();
	rect.SetCenter(pos.x, pos.y + (kHeight / 2), kWidth, kHeight);

	//地面に着地したらIdleかMoveへ遷移
	if (pos.y >= kGround)
	{
		if (input.IsPressed("left") || input.IsPressed("right"))
		{
			player.ChangeState(std::make_unique<Move>());
		}
		else
		{
			player.ChangeState(std::make_unique<Idle>());
		}
	}

}

