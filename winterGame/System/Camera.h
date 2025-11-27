#pragma once
#include"base/GameObject.h"
class Player;

class Camera :public GameObject
{
public:
	Camera();
	~Camera();

	void Init();
	void Init(Player& player);
	void Update();
	void Update(Player& player);
	void Draw();

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

//DrawOffsetのゲッター
	Vector2 GetDrawOffset() { return drawOffset_; }

//	Vector2 VLerp(const Vector2& stert, const Vector2& end, float t);

private:
	Vector2 drawOffset_;
};

