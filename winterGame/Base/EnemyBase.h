#pragma once
#include "GameObject.h"
#include<memory>
#include<vector>

/// <summary>
/// 敵の画像の切り取りラインをenumで決める
/// </summary>
enum class EnemyGraphCutNo
{
	one,
	two
};

enum class EnemyType
{
	walk,
	fly,
};

class Player;
class EnemyStateBase;
class Camera;
/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase :public GameObject
{
public:

	std::unique_ptr<EnemyStateBase>state_;

	EnemyBase(const int hp, const Vector2 vel, const Vector2 pos,const int handle , std::shared_ptr<Player>player, bool isPlayerOnRight,int nockBackTime,EnemyType enemyType);
	virtual~EnemyBase();
	virtual void Init()override = 0;
	virtual void Update()override = 0;
	virtual void Draw()override = 0;
	virtual void Draw(Camera& camera) = 0;

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

	virtual void ChangeState(std::unique_ptr<EnemyStateBase> newState) = 0;

	//ポジションのゲッター・セッター
	Vector2 GetPosition() const { return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocotyのゲッター・セッター
	Vector2 GetVelocity() const { return velocity_; }
	void SetVelocity(const Vector2& vel) { velocity_ = vel; }

	//Rectのゲッター
	Rect& GetHitRect() { return rect_; }

	//<画像ハンドルのセッター>
	int GetGraph() { return graphHandle_; }
	void SetGraph(int handle) { graphHandle_ = handle; }

	//プレイヤーが右にいるかどうかのフラグのゲッター・セッター
	bool GetPlayerOnRight() { return isPlayerOnRight_; }
	void SetPlayerOnRight(bool flag) { isPlayerOnRight_ = flag; }

	//プレイヤーの参照のゲッター
	std::shared_ptr<Player> GetPlayer()const { return player_; }

	int GetNockBackTime() { return nockBackTime_; }
	void SetNockBackTime(int time) { nockBackTime_ = time; }

	//死んでいるかどうかフラグのゲッター・セッター
	bool GetIsDead() { return isDead_; }
	void SetIsDead(bool isDead) { isDead_ = isDead; }

	bool GetIsAlive() { return isAlive_; }
	void SetIsAlive(bool isAlive) { isAlive_ = isAlive; }

	bool GetIsInhaled() { return isInhaled_; }
	void SetIsInhaled(bool isInhaled) { isInhaled_ = isInhaled; }

	//歩くだけの敵の画像の切り取り位置のセッター
	void SetEnemyGraphCutNo(EnemyGraphCutNo egcn) { graphCutNo_ = egcn; }
	/// <summary>
	/// 重力用関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// 移動を適用する関数
	/// </summary>
	void ApplyMovement();

protected:
	//体力
	int hp_;
	//移動速度
	Vector2 velocity_;

	bool isDead_;

	bool isAlive_;

	bool isInhaled_;
	//画像ハンドル
	int graphHandle_;

	//プレイヤーのポインタを入れる変数
	std::shared_ptr<Player>player_;

	//プレイヤーが右にいるかどうかのフラグ
	bool isPlayerOnRight_;

	//ノックバックの時間
	int nockBackTime_;

	//歩くだけの敵の画像切り取り位置を決める
	EnemyGraphCutNo graphCutNo_;
	//エネミーの種類
	EnemyType enemyType_;
};
/// <summary>
/// エネミーステート基底クラス
/// </summary>
class EnemyStateBase
{
public:
	virtual ~EnemyStateBase() = default;
	virtual void Enter(EnemyBase& enemy)  = 0;
	virtual void Update(EnemyBase& enemy) = 0;
	virtual void Exit(EnemyBase& enemy)  = 0;
};

/// <summary>
/// Move状態クラス
/// </summary>
class Move : public EnemyStateBase
{
	void Enter(EnemyBase& enemy)override;
	void Update(EnemyBase& enemy)override;
	void Exit(EnemyBase& enemy)override;
};

/// <summary>
/// Walk状態クラス
/// </summary>
class Walk : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
	void Exit(EnemyBase& enemy) override;
};
/// <summary>
/// Death状態クラス
/// </summary>
class Death : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
	void Exit(EnemyBase& enemy) override;
};
/// <summary>
/// None状態クラス
/// (画面外状態)
/// </summary>
class None : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
	void Exit(EnemyBase& enemy) override;
};
/// <summary>
/// 吸い込まれている状態クラス
/// </summary>
class Inhaled : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
	void Exit(EnemyBase& enemy) override;
};




