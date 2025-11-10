#pragma once
#include "GameObject.h"
/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase :public GameObject
{
public:
	EnemyBase(const int hp,const Vector2 vel);
	virtual~EnemyBase();
	virtual void Init()override = 0;
	virtual void Update()override = 0;
	virtual void Draw()override = 0;
protected:
	//体力
	int hp_;
	//移動速度
	Vector2 velocity_;
};

