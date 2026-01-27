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
#include"Stage/Stage.h"
#include"EffectManager.h"

Shot::Shot(bool isRight,Vector2 pos,int graphHandle, std::shared_ptr<EffectManager>effectManager):
	GameObject(pos),
	velocity_({0.0f,0.0f}),
	graphHandle_(graphHandle),
	isRight_(isRight),
	isActive_(true),
	effectManager_(effectManager)
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
	return CollisionLayers::kEnemy|
		CollisionLayers::kBoss;
}

void Shot::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		isActive_ = false;
		scene_->PushRequest({SceneRequestType::PlaySE,0.0f,0,"enemyDead"});
	}

	if (other.GetCollisionLayer() & CollisionLayers::kBoss)
	{
		effectManager_->Generate(position_);
		isActive_ = false;
		scene_->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"enemyDead" });
	}
}

void Shot::MapCollisionX(const Stage& stage, Rect tileRect)
{
	if (stage.IsCollision(rect_, tileRect))
	{
		isActive_ = false;
	}
}

void Shot::SetScene(GameScene* scene)
{
	scene_ = scene;
}
