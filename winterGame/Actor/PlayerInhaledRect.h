#pragma once
#include "GameObject.h"
#include<memory>
#include<vector>

class Player;
class EnemyBase;
class Camera;
class PlayerInhaledRect :public GameObject
{
public:
	PlayerInhaledRect(Vector2 pos, std::shared_ptr<Player>player);
	~PlayerInhaledRect();

	void Init()override;
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

	//マップタイルと当たった時の処理を行う関数
	void OnCollisionTile(const Rect& tileRect)override;

	//プレイヤーの参照のゲッター
	std::shared_ptr<Player> GetPlayer()const { return player_; }

	bool GetIsActive() { return isActive_; }
	void SetIsActive(bool isActive) { isActive_ = isActive; }
private:
	bool isActive_;
	bool isRight_;

	std::shared_ptr<Player>player_;
};

