#include<DxLib.h>
#include "WalkEnemy.h"
#include"../System/Rect.h"
#include"../Player/Player.h"
#include<memory>
#include"../System/Camera.h"
#include"../Player/PlayerState/HitState.h"
namespace
{
	constexpr int kHp = 1;
	constexpr float kSpeed = 1.5f;

	constexpr int kWidth = 32;
	constexpr int kHeight = 32;
	constexpr float kSize = 2.0f;

	constexpr float kGravity = 0.5f;
	constexpr int kGround = 400;
	constexpr float kMaxSpeed = 1.5f;

	constexpr float kNockbackSpeed = 4.0f;
	constexpr float kNockBackTimeMax = 20;
}

WalkEnemy::WalkEnemy(Vector2 pos,EnemyImages& imgs,std::shared_ptr<Player>player) :
	images_(imgs),
	EnemyBase(kHp,{0,0}, pos,imgs,images_.walk_walk,player,false,0)

{
	state_ = std::make_unique<Walk>();
	currentImage_ = images_.walk_walk;
}

WalkEnemy::~WalkEnemy()
{
}

void WalkEnemy::Init()
{
	
}

void WalkEnemy::Update()
{
	state_->Update(*this);
}
void WalkEnemy::Draw()
{

}

void WalkEnemy::Draw(Camera& camera)
{
	DrawRectRotaGraph(position_.x +camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		0, 0, kWidth, kHeight,
		kSize,0, currentImage_, true);
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight * 0.5f)+camera.GetDrawOffset().y, kWidth, kHeight);
	rect_.Draw(0x0000ff,false);
}


void WalkEnemy::ChangeState(std::unique_ptr<EnemyStateBase>newState)
{
	state_->Exit(*this);
	state_ = std::move(newState);
	state_->Enter(*this);
}

void Walk::Enter(EnemyBase& enemy)
{
	enemy.SetGraph(enemy.GetImages().walk_walk);
}
void Walk::Update(EnemyBase& enemy)
{
	enemy.Gravity();

	Vector2 vel = enemy.GetVelocity();
	vel.x -= kSpeed;

	if(vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	enemy.SetVelocity(vel);

	enemy.ApplyMovement();

	auto player = enemy.GetPlayer();
	Vector2 pos = enemy.GetPosition();
	Rect& rect = enemy.GetHitRect();
//	rect.SetCenter(pos.x,pos.y + (kHeight/2),kWidth ,kHeight);
	Rect& playerRect = player->GetHitRect();
	//当たり判定
	if (rect.IsCollision(playerRect))
	{
		//プレイヤーが右にいるか左にいるかを判定
		float enemyToPlayer = player->GetPosition().x - enemy.GetPosition().x;
		bool isplayerOnRight = enemyToPlayer > 0 ? true : false;
		enemy.SetPlayerOnRight(isplayerOnRight);

		//エネミーの状態遷移
		enemy.ChangeState(std::make_unique<Death>());
		//プレイヤーの状態遷移
		player->ChangeState(std::make_unique<PlayerState::HitState>());
	}
}

void Walk::Exit(EnemyBase& enemy)
{

}

void Death::Enter(EnemyBase& enemy)
{
	enemy.SetGraph(enemy.GetImages().walk_death);
}
void Death::Update(EnemyBase& enemy)
{
	Vector2 vel = enemy.GetVelocity();
	bool isPlayerOnRight = enemy.GetPlayerOnRight();

	if(isPlayerOnRight)
	{
		vel.x = -kNockbackSpeed;
	}
	else
	{
		vel.x = kNockbackSpeed;
	}

	enemy.Gravity();

	enemy.SetVelocity(vel);

	enemy.ApplyMovement();

	auto nockBackTime = enemy.GetNockBackTime();
	nockBackTime += 1;
	if (nockBackTime >= kNockBackTimeMax)
	{
		enemy.ChangeState(std::make_unique<None>());
	}
	enemy.SetNockBackTime(nockBackTime);
}

void Death::Exit(EnemyBase& enemy)
{
	//isDead_をtrueにする
	enemy.SetIsDead(true);
}

void None::Enter(EnemyBase& enemy)
{
}
void None::Update(EnemyBase& enemy)
{
}
void None::Exit(EnemyBase& enemy)
{
}

void Inhaled::Enter(EnemyBase& enemy)
{
	enemy.SetGraph(enemy.GetImages().walk_inhaled);
	enemy.SetVelocity({ 0,0 });
}

void Inhaled::Update(EnemyBase& enemy)
{
	Rect& rect = enemy.GetHitRect();
	auto player = enemy.GetPlayer();
	Rect& playerRect = player->GetHitRect();
	//当たり判定
	if (rect.IsCollision(playerRect))
	{
		//エネミーの状態遷移
		enemy.ChangeState(std::make_unique<Death>());
	}
	enemy.Gravity();
	enemy.ApplyMovement();
}
void Inhaled::Exit(EnemyBase& enemy)
{
	
}

