#pragma once
#include "GameObject.h"
class Player;
/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase :public GameObject
{
public:
	EnemyBase(const int hp,const Vector2 vel,const Vector2 pos);
	virtual~EnemyBase();
	virtual void Init()override = 0;
	virtual void Update()override = 0;
	virtual void Draw()override = 0;

	Vector2 GetPosition() const { return position_; }

	Rect GetHitRect() { return rect_; }

	bool GetIsDead() { return isDead_; }

	void SetVelocity(const Vector2& vel) { velocity_ = vel; }
protected:
	//体力
	int hp_;
	//移動速度
	Vector2 velocity_;

	bool isDead_;
};

