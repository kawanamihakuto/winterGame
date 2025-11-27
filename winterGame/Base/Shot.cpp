#include "Shot.h"
#include<memory>
#include<vector>
#include"../Collision/Rect.h"
#include"../Player/Player.h"
#include"../Base/EnemyBase.h"
#include<DxLib.h>
#include"../System/Camera.h"
#include"../Actor/WalkEnemy.h"
#include"../System/Lerp.h"
#include"../Player/PlayerState/InhaleHoldState.h"



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
