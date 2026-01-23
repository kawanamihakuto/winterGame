#pragma once
#include"base/GameObject.h"
class Player;

class Camera :public GameObject
{
public:
	Camera();
	~Camera();

	void Init();
	void Init(int stageNo);
	void SetTarget(const Vector2& pos);
	void Update();
	void Draw();

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

	Vector2 WorldToScreen(const Vector2& world)const;
//DrawOffsetのゲッター
	Vector2 GetDrawOffset() { return drawOffset_; }

	void StartShake(float power ,int time);

	void ShakeUpdate();
private:
	Vector2 drawOffset_;
	Vector2 target_;
	int stageNo_;

	float shakePower_;
	int shakeTime_;
	Vector2 shakeOffset_;
};

