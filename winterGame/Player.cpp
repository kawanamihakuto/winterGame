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

	constexpr int kMoveSpeed = 10;
	constexpr int kGravity = 5;
}

Player::Player() :
	direction_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(true)
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
	state_->Update(*this,input);

	if (position_.y >= kGround)
	{
		position_.y = kGround;
	}

}

void Player::Draw()
{
	state_->Draw(*this);
}

void Player::ChangeState(std::unique_ptr<StateBase> newState)
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
	direction_.y += 1.0f;
	ApplyMovement(kGravity);
}

void Player::ApplyMovement(float speed)
{
	if (direction_.x == 0.0f && direction_.y == 0.0f)
	{
		return;
	}

	direction_.Normalize();
	position_ += direction_ * speed;
}

void Idle::Update(Player& player, Input& input)
{
	player.Gravity();
	if (input.IsPressed("left")&& input.IsPressed("right"))
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
void Idle::Draw(Player& player)
{
	Vector2& pos = player.GetPosition();
	int& idleH = player.GetIdleGraph();
	DrawRectGraph(pos.x,pos.y,0,0,kWidth,kHeight,idleH,true);

#ifdef _DEBUG
	DrawString(0, 0, "Idle", 0xffffff);
#endif // _DEBUG
}

void Move::Update(Player& player, Input& input)
{
	Vector2 dir{ 0,0 };

	if (input.IsPressed("left"))
	{
		dir.x -= 1.0f;
	}
	if (input.IsPressed("right"))
	{
		dir.x += 1.0f;
	}

	if (dir.x == 0.0f)
	{
		player.ChangeState(std::make_unique<Idle>());
	}

	player.SetDirection(dir);

	player.ApplyMovement(kMoveSpeed);

}
void Move::Draw(Player& player)
{
	Vector2& pos = player.GetPosition();
	int& idleH = player.GetIdleGraph();
	DrawRectGraph(pos.x, pos.y, 0, 0, kWidth, kHeight, idleH, true);

#ifdef _DEBUG
	DrawString(0,0,"Move",0xffffff);
#endif // _DEBUG

	
}

void Jump::Enter(Player& player)
{

}

void Jump::Update(Player& player, Input& input)
{
}
void Jump::Draw(Player& player)
{
}
