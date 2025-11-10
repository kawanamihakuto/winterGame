#pragma once
#include "GameObject.h"
#include<memory>
class StateBase;
class Player;
class Input;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public GameObject
{
public:
	//フレンドにする
	friend StateBase;

	//現在のステートを入れる変数
	std::unique_ptr<StateBase>state_;

	Player(int idleH);
	~Player();

	void Init()override;
	void Update()override;
	void Update(Input& input);
	void Draw()override;

	//ポジションのゲッター・セッター
	 Vector2& GetPosition(){ return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocityのゲッター・セッター
	Vector2& GetVelocity() { return velocity_; }
	void SetVelocity(const Vector2& dir) { velocity_ = dir; }
	
	//<画像ハンドルのセッター>
	void SetIdleGraph(int handle) { idleH_ = handle; }
	int& GetIdleGraph() { return idleH_; }

	/// <summary>
	/// ステート切り替えの関数
	/// </summary>
	/// <param name="newState">切り替えるステート</param>
	void ChangeState(std::unique_ptr<StateBase>newState);

	/// <summary>
	/// 重力用関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// 移動を適用する関数
	/// </summary>
	void ApplyMovement();

private:
	//速度ベクトル
	Vector2 velocity_;
	//地面にいるかどうか
	bool isGround_;
	//Idle画像ハンドル
	int idleH_;
};
/// <summary>
/// ステートの基底クラス
/// </summary>
class StateBase
{
public:
	virtual ~StateBase() = default;
	virtual void Enter(Player& player){};
	virtual void Update(Player& player,Input& input) = 0;
	virtual void Draw(Player& player) {};
	virtual void Exit(Player& player) {};
};
/// <summary>
/// Idle状態クラス
/// </summary>
class Idle : public StateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player,Input&input) override;
	void Draw(Player& player)override;
};
/// <summary>
/// Move状態クラス
/// </summary>
class Move : public StateBase
{
public:
	void Update(Player& player, Input& input) override;
	void Draw(Player& player)override;
};
/// <summary>
/// Jamp状態クラス
/// </summary>
class Jump : public StateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Draw(Player& player)override;
};

