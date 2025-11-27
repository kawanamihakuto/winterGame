#include "Shot.h"
#include<memory>
#include<vector>
#include"Collision/Rect.h"
#include"Player.h"
#include"Base/EnemyBase.h"
#include<DxLib.h>
#include"Camera.h"
#include"WalkEnemy.h"
#include"Lerp.h"
#include"InhaleHoldState.h"



Shot::Shot(bool isRight,Vector2 pos,int graphHandle):
	GameObject(pos),
	velocity_({0.0f,0.0f}),
	graphHandle_(graphHandle),
	isRight_(isRight),
	isActive_(true)
{
}

Shot::~Shot()
{

}

Rect Shot::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Shot::GetCollisionLayer() const
{
	return CollisionLayers::kAttack;
}

CollisionLayer Shot::GetHitMask() const
{
	return CollisionLayers::kEnemy;
}

void Shot::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		isActive_ = false;
	}
}
