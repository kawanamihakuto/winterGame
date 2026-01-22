#pragma once
#include "GameObject.h"
#include"BossState/BossStateBase.h"
#include<memory>
class Camera;
class BossStateBase;
class BossBase : public GameObject
{
public:
	BossBase(Vector2 pos,int graphHandle);
	virtual  ~BossBase();
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

	virtual void ChangeState(std::unique_ptr<BossState::BossStateBase> newState) = 0;

	void SetVelocity(Vector2 vel) { velocity_ = vel; }
	
	Vector2 GetPosition() { return position_; }
	void SetPosition(Vector2 pos) { position_ = pos; }

	int GetHP() { return hp_; }

	int GetMaxHP();

protected:
	//現在のステートを入れる変数
	std::unique_ptr<BossState::BossStateBase>state_;
	//体力
	int hp_ = 0;
	//移動速度
	Vector2 velocity_;
	//画像ハンドル
	int graphHandle_;
};

