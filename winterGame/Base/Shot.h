#pragma once
#include"Base/GameObject.h"
#include<memory>
#include<vector>
class Player;
class EnemyBase;
class Camera;
class Stage;
class EffectManager;
class Shot :public GameObject
{
public:
	Shot(bool isRight,Vector2 pos,int graphHandle,std::shared_ptr<EffectManager>effectManager);
	virtual ~Shot();

	void Init()override = 0;
	virtual void Init(std::shared_ptr<Player>player) = 0;
	void Update()override = 0;
	virtual void Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies,Stage& stage) = 0;
	void Draw()override = 0;
	virtual void Draw(Camera& camera) = 0;

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

	bool GetIsActive() { return isActive_; }
	void SetIsActive(bool isActive) { isActive_ = isActive; }

	void MapCollisionX(const Stage& stage,Rect tileRect);
protected:
	std::shared_ptr<EffectManager>effectManager_;
	Vector2 velocity_;
	int graphHandle_;
	bool isRight_;
	bool isActive_;
};

