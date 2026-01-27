#pragma once
#include "GameObject.h"
#include"BossState/BossStateBase.h"
#include<memory>
class Camera;
class BossStateBase;
class Player;
class BossBullet;
class EffectManager;
class GameScene;
class BossBase : public GameObject
{
public:
	BossBase(Vector2 pos,int graphHandle,std::shared_ptr<Player>player,std::shared_ptr<EffectManager>effectManager);
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

	void OnShot() { isShot_ = true; }
	bool GetShotFlag() { return isShot_; }
	void ResetShotFlag() { isShot_ = false; }

	std::shared_ptr<Player> GetPlayer() { return player_; }

	std::shared_ptr<EffectManager> GetEffectManager() { return effectManager_; }

	bool GetIsActive() { return isActive_; }

	void OnDamage();

	bool IsRequestCameraShake() { return requestCameraShake_; }

	void SetCameraShakeRequest(bool isCameraShake) { requestCameraShake_ = isCameraShake; }

	bool IsRequestModeChange() { return requestSceneModeChange_; }

	void SetModeChangeRequest(bool isSceneMode) { requestSceneModeChange_ = isSceneMode; }

	bool isDead() { return isDead_; }

	void SetOffset(Vector2 offset) { ShakeOffset_ = offset; }

	void SetScene(GameScene* scene);

	GameScene* GetScene() { return scene_; }
protected:
	//現在のステートを入れる変数
	std::unique_ptr<BossState::BossStateBase>state_;
	//体力
	int hp_ = 0;
	//移動速度
	Vector2 velocity_;
	//画像ハンドル
	int graphHandle_;
	//shotフラグ
	bool isShot_;

	std::shared_ptr<Player>player_;

	bool isActive_;

	int damageTimer_;

	bool requestCameraShake_;

	float isDead_;

	bool requestSceneModeChange_;

	Vector2 ShakeOffset_;

	std::shared_ptr<EffectManager>effectManager_;

	GameScene* scene_ = nullptr;
};

