#pragma once
#include "GameObject.h"

class Camera;
class Door :public GameObject
{
public:
	Door(int graphHandle);
	virtual ~Door();

	void Init()override;
	void Init(int stageNo);
	void Update()override;
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

private :
	int graphHandle_;
};

