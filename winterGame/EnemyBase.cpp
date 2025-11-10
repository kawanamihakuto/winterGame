#include "EnemyBase.h"

EnemyBase::EnemyBase(const int hp,const Vector2 vel) :GameObject({0,0}),
hp_(hp),
velocity_(vel)
{ 
}

EnemyBase::~EnemyBase()
{
}
