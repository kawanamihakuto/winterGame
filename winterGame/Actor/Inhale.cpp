#include "Inhale.h"
#include<memory>
#include<vector>
#include"../System/Rect.h"
#include"Player.h"
#include"../Base/EnemyBase.h"
constexpr int kWidth = 32;
constexpr int kHeight = 32;
constexpr int kSize = 2;

constexpr int kOffsetX = 20;

Inhale::Inhale(Vector2 pos) : GameObject(pos)
{
}

Inhale::~Inhale()
{
}

void Inhale::Init()
{
}

void Inhale::Update()
{
}

void Inhale::Update(std::shared_ptr<Player>player,std::vector<std::shared_ptr<EnemyBase>>enemies)
{
	
	Vector2 playerPos = player->GetPosition();

	position_.x = playerPos.x + kOffsetX;

	rect_.SetCenter(position_.x, position_.y, kWidth, kHeight);

	for (auto& enemies : enemies)
	{
		if (rect_.IsCollision(enemies->GetHitRect()))
		{
			enemies->SetVelocity(position_ - enemies->GetPosition());
		}
	}
}

void Inhale::Draw()
{
}
