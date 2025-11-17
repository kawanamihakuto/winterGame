#pragma once
#include "GameObject.h"
#include<memory>
#include<vector>

struct EnemyImages
{
	int walk_walk;
	int walk_death;
};

class Player;
class EnemyStateBase;
/// <summary>
/// エネミー基底クラス
/// </summary>
class EnemyBase :public GameObject
{
public:
	EnemyBase(const int hp, const Vector2 vel, const Vector2 pos,EnemyImages& imgs ,const int currentImage, std::shared_ptr<Player>player, bool isPlayerOnRight,int nockBackTime);
	virtual~EnemyBase();
	virtual void Init()override = 0;
	virtual void Update()override = 0;
	virtual void Draw()override = 0;
	//ポジションのゲッター・セッター
	Vector2 GetPosition() const { return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocotyのゲッター・セッター
	Vector2 GetVelocity() const { return velocity_; }
	void SetVelocity(const Vector2& vel) { velocity_ = vel; }

	//Rectのゲッター
	Rect& GetHitRect() { return rect_; }

	//<画像ハンドルのセッター>
	int GetGraph() { return currentImage_; }
	void SetGraph(int handle) { currentImage_ = handle; }

	//プレイヤーが右にいるかどうかのフラグのゲッター・セッター
	bool GetPlayerOnRight() { return isPlayerOnRight_; }
	void SetPlayerOnRight(bool flag) { isPlayerOnRight_ = flag; }

	//プレイヤーの参照のゲッター
	std::shared_ptr<Player> GetPlayer()const { return player_; }

	//imagesのゲッター
	const EnemyImages& GetImages() const { return images_; }

	int GetNockBackTime() { return nockBackTime_; }
	void SetNockBackTime(int time) { nockBackTime_ = time; }

	//死んでいるかどうかフラグのゲッター・セッター
	bool GetIsDead() { return isDead_; }
	void SetIsDead(bool isDead) { isDead_ = isDead; }

	/// <summary>
	/// ステート切り替えの関数
	/// </summary>
	/// <param name="newState">新しいステート</param>
	void ChangeState(std::unique_ptr<EnemyStateBase>newState,EnemyBase& enemy);

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

	//現在の画像
	int currentImage_;

	EnemyImages images_;

	std::shared_ptr<Player>player_;

	//プレイヤーが右にいるかどうかのフラグ
	bool isPlayerOnRight_;

	//ノックバックの時間
	int nockBackTime_;

	//現在のステートを入れる変数
	std::unique_ptr<EnemyStateBase> state_;
};

/// <summary>
/// ステート基底クラス
/// </summary>
class EnemyStateBase
{
public:
	virtual ~EnemyStateBase() = default;
	virtual void Enter(EnemyBase& enemy) {};
	virtual void Update(EnemyBase& enemy) = 0;
	virtual void Exit(EnemyBase& enemy) {};
};
/// <summary>
/// Walk状態クラス
/// </summary>
class Walk : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
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
};
/// <summary>
/// 吸い込まれている状態クラス
/// </summary>
class Inhaled : public EnemyStateBase
{
	void Enter(EnemyBase& enemy) override;
	void Update(EnemyBase& enemy) override;
};



