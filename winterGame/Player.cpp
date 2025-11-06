#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
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

void Player::Draw()
{
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

void Move::Update(Player& player)
{
}

void Jump::Enter(Player& player)
{

}

void Jump::Update(Player& player)
{
}

