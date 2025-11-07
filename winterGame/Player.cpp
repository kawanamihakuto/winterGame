#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
#include"Rect.h"

namespace
{
	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
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
	state_->Update(*this);
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

void Idle::Update(Player& player)
{
	
}
void Idle::Draw(Player& player)
{
	Vector2& pos = player.GetPosition();
	int& idleH = player.GetIdleGraph();
	DrawRectGraph(pos.x,pos.y,0,0,kWidth,kHeight,idleH,true);
}

void Move::Update(Player& player)
{
}
void Move::Draw(Player& player)
{
}

void Jump::Enter(Player& player)
{

}

void Jump::Update(Player& player)
{
}
void Jump::Draw(Player& player)
{
}

