#include "EnemyBase.h"
#include"../Actor/Player.h"
#include<memory>

constexpr int kGround = 400;

EnemyBase::EnemyBase(const int hp,const Vector2 vel,const Vector2 pos, const int currentImage, std::shared_ptr<Player>player, bool isPlayerOnRight, int nockBackTime) :GameObject(pos),
hp_(hp),
velocity_(vel),
isDead_(false),
player_(player),
currentImage_(currentImage),
isPlayerOnRight_(isPlayerOnRight),
nockBackTime_(nockBackTime)
{ 
}

EnemyBase::~EnemyBase()
{
}

