#include "EnemyBase.h"

EnemyBase::EnemyBase(const int hp,const Vector2 vel,const Vector2 pos) :GameObject(pos),
hp_(hp),
velocity_(vel)
{ 
}

EnemyBase::~EnemyBase()
{
}
