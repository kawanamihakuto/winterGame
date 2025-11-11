#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
#include"Rect.h"
#include"Input.h"
namespace
{
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;

	constexpr int kGround = 400;

	constexpr float kMoveSpeed = 0.5f;
	constexpr float kGravity = 4.0f;
	constexpr float kJumpPower = 5.0f;

	constexpr float kMaxSpeed = 2.0f;
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
	DrawRectGraph(pos.x, pos.y, 0, 0, kWidth, kHeight, currentImage_, true);
}

void Player::ChangeState(std::unique_ptr<PlayerStateBase> newState)
{
	if (state_)
	{
		state_->Exit(*this);
		state_ = std::move(newState);
		state_->Enter(*this);
	}
}

void Player::Gravity()
{
	velocity_.y += 0.5f;
	ApplyMovement();
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
	player.SetGraph(player.GetImages().idle);
	Vector2 vel = player.GetVelocity();
	vel.x = 0.0f;
	player.SetVelocity(vel);
}

void Idle::Update(Player& player, Input& input)
{
	player.Gravity();
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<Move>());
	}
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<Move>());
	}
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<Jump>());
	}


}


void Move::Enter(Player& player)
{
	player.SetGraph(player.GetImages().move);
}

void Move::Update(Player& player, Input& input)
{
	player.Gravity();

	Vector2 vel = player.GetVelocity();

	if (input.IsPressed("left"))
	{
		vel.x -= kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		vel.x += kMoveSpeed;
	}
	
	if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<Jump>());
		return;
	}

	vel.x *= kFriction;

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

	if (vel.x <= 0.1f&&vel.x >= -0.1)
	{
		player.ChangeState(std::make_unique<Idle>());
	}

}


void Jump::Enter(Player& player)
{
	player.SetGraph(player.GetImages().jump);
	Vector2 vel = player.GetVelocity();
	vel.y = -kJumpPower;
	player.SetVelocity(vel);
}

void Jump::Update(Player& player, Input& input)
{
	player.Gravity();

	Vector2 pos = player.GetPosition();

	Vector2 vel = player.GetVelocity();

	if (input.IsPressed("left"))
	{
		vel.x -= kMoveSpeed * 0.2f;
	}
	if (input.IsPressed("right"))
	{
		vel.x += kMoveSpeed * 0.2f;
	}

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

