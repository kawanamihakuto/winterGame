#pragma once
#include "GameObject.h"
#include<memory>

enum ItemType
{
	dragonFruit
};
class Player;
class Camera;
class Item :public GameObject
{
public:
	Item(std::shared_ptr<Player>player,ItemType itemType,Vector2 pos);
	~Item();
	void Init()override = 0;
	virtual void Init(int stageNo) = 0;
	void Update()override = 0;
	void Draw()override = 0;
	virtual void Draw(Camera& camera) = 0;
	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	virtual CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	virtual CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	virtual void OnCollision(GameObject& other) override;

	ItemType GetItemType() { return itemType_; }

	bool GetIsActive() { return isActive_; }

private:
	std::shared_ptr<Player>player_;

	ItemType itemType_;

	bool isActive_;
};

