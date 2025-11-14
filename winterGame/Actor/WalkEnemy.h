#pragma once
#include "../Base/EnemyBase.h"
#include <memory>

class WalkEnemy;
class WalkEnemyStateBase;
class Rect;
class Player;
/// <summary>
/// WalkEnemyの各画像
/// </summary>
struct WalkEnemyImages
{
	int walk;
	int death;
};

/// <summary>
/// 歩く敵クラス
/// </summary>
class WalkEnemy :public EnemyBase
{
public:
	//現在のステートを入れる変数
	std::unique_ptr<WalkEnemyStateBase> state_;

	WalkEnemy(Vector2 pos,WalkEnemyImages& imgs,std::shared_ptr<Player>player);
	~WalkEnemy ();
	void Init()override;
	void Update() override;
	void Draw() override;
	/// <summary>
	/// ステート切り替えの変数
	/// </summary>
	/// <param name="newState"></param>
	void ChangeState(std::unique_ptr<WalkEnemyStateBase>newState);

	//ポジションのゲッター・セッター
	Vector2 GetPosition() const{ return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocotyのゲッター・セッター
	Vector2 GetVelocity() const{ return velocity_; }
	void SetVelocity(const Vector2& vel) { velocity_ = vel; }

	//Rectのゲッター・セッター
	 Rect& GetHitRect(){ return rect_; }

	//<画像ハンドルのセッター>
	 int GetGraph() { return currentImage_; }
	void SetGraph(int handle) { currentImage_ = handle; }

	//プレイヤーが右にいるかどうかのフラグのゲッター・セッター
	bool GetPlayerOnRight() { return isPlayerOnRight_; }
	void SetPlayerOnRight(bool flag) { isPlayerOnRight_ = flag; }

	//プレイヤーの参照のゲッター
	std::shared_ptr<Player> GetPlayer()const { return player_; }

	//imagesのゲッター
	const WalkEnemyImages& GetImages() const { return images_; }

	int GetNockBackTime() { return nockBackTime_; }
	void SetNockBackTime(int time) { nockBackTime_ = time; }

	//死んでいるかどうかフラグのゲッター・セッター
	bool GetIsDead() { return isDead_; }
	void SetIsDead(bool isDead) { isDead_ = isDead; }

	/// <summary>
	/// 重力用関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// 移動を適用する関数
	/// </summary>
	void ApplyMovement();


private:
	//画像ハンドルをまとめて持つ
	WalkEnemyImages images_;
	//現在の画像
	int currentImage_;

	std::shared_ptr<Player>player_;
	
	//プレイヤーが右にいるかどうかのフラグ
	bool isPlayerOnRight_;

	//ノックバックの時間
	int nockBackTime_;

	//死んでいるかどうかフラグ
	bool isDead_;
};

/// <summary>
/// ステート基底クラス
/// </summary>
class WalkEnemyStateBase
{
public:
	virtual ~WalkEnemyStateBase() = default;
	virtual void Enter(WalkEnemy& enemy) {};
	virtual void Update(WalkEnemy& enemy) = 0;
	virtual void Exit(WalkEnemy& enemy) {};
};
/// <summary>
/// Walk状態クラス
/// </summary>
class Walk : public WalkEnemyStateBase
{
	void Enter(WalkEnemy& enemy) override;
	void Update(WalkEnemy& enemy) override;
};
/// <summary>
/// Death状態クラス
/// </summary>
class Death : public WalkEnemyStateBase
{
	void Enter(WalkEnemy& enemy) override;
	void Update(WalkEnemy& enemy) override;
	void Exit(WalkEnemy& enemy) override;
};
/// <summary>
/// None状態クラス
/// (画面外状態)
/// </summary>
class None : public WalkEnemyStateBase
{
	void Enter(WalkEnemy& enemy) override;
	void Update(WalkEnemy& enemy) override;
};