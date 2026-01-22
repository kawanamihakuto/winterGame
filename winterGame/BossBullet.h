#pragma once
#include "GameObject.h"
#include"System/Geometry.h"
#include<memory>
#include<vector>
class BossBase;
class Player;
class Camera;
class BossBullet :public GameObject
{
public:
	BossBullet(Vector2 pos,Vector2 playerPos, int graphHandle);
	virtual ~BossBullet();

	void Init()override;
	void Update()override ;
	void Update(Camera& camera);
	void Draw()override;
	void Draw(Camera& camera);

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

	bool GetIsActive() { return isActive_; }

private:
	int graphHandle_;
	Vector2 velocity_;
	bool isActive_;
	Vector2 playerPos_;
	Vector2 vector_;
};

