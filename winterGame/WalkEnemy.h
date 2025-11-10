#pragma once
#include "EnemyBase.h"
#include <memory>
/// <summary>
/// 歩く敵クラス
/// </summary>
class WalkEnemy :public EnemyBase
{
public:
	//フレンドにする
	friend class StateBase;
	//現在のステートを入れる変数
	std::unique_ptr<StateBase> state_;

	WalkEnemy(Vector2& firstPos);
	~WalkEnemy ();
	void Init()override;
	void Update() override;
	void Draw() override;
	/// <summary>
	/// ステート切り替えの変数
	/// </summary>
	/// <param name="newState"></param>
	void ChangeState(std::unique_ptr<StateBase>newState);
	/// <summary>
	/// 移動を適用する関数。
	/// </summary>
	void ApplyMovement();

	//ポジションのゲッター・セッター
	Vector2& GetPosition() { return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocotyのゲッター・セッター
	Vector2& GetVelocity() { return velocity_; }
	void SetVelocity(const Vector2& vel) { velocity_ = vel; }


};

/// <summary>
/// ステート基底クラス
/// </summary>
class StateBase
{
public:
	virtual ~StateBase() = default;
	virtual void Enter(WalkEnemy& enemy) {};
	virtual void Update(WalkEnemy& enemy) = 0;
	virtual void Draw(WalkEnemy& enemy) {};
	virtual void Exit(WalkEnemy& enemy) {};
};
/// <summary>
/// Walk状態クラス
/// </summary>
class Walk : public StateBase
{
	void Update(WalkEnemy& enemy) override;
};
/// <summary>
/// Death状態クラス
/// </summary>
class Death : public StateBase
{
	void Enter(WalkEnemy& enemy) override;
	void Update(WalkEnemy& enemy) override;	
	void Exit(WalkEnemy& enemy) override;
};
/// <summary>
/// None状態クラス
/// (画面外状態)
/// </summary>
class None : public StateBase
{
	void Enter(WalkEnemy& enemy) override;
	void Update(WalkEnemy& enemy) override;
};