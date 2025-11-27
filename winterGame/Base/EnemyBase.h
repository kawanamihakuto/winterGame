#pragma once
#include "GameObject.h"
#include<memory>
#include<vector>

struct EnemyImages
{
	int walk_walk;
	int walk_death;
	int walk_inhaled;
};
/// <summary>
/// 敵の画像の切り取りラインをenumで決める
/// </summary>
enum class EnemyGraphCutNo
{
	one,
	two
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

	EnemyBase(const int hp, const Vector2 vel, const Vector2 pos,const int handle , std::shared_ptr<Player>player, bool isPlayerOnRight,int nockBackTime);
	virtual~EnemyBase();
	virtual void Init()override = 0;
	virtual void Update()override = 0;
	virtual void Draw()override = 0;
	virtual void Draw(Camera& camera) = 0;

	bool CheckCollision(const Rect& other)const override;
	void OnHit(Rect* other)override;

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




