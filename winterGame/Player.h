#pragma once
#include "GameObject.h"
#include<memory>
class StateBase;
class Player;
class Player :public GameObject
{
public:

	std::unique_ptr<StateBase>state_;

	Player();
	~Player();

	void Init()override;
	void Update()override;
	void Draw()override;
	/// <summary>
	/// ステート切り替えの関数
	/// </summary>
	/// <param name="newState">切り替えるステート</param>
	void ChangeState(std::unique_ptr<StateBase>newState);
private:
	Vector2 direction_;
	bool isGround_;
};
/// <summary>
/// ステートの基底クラス
/// </summary>
class StateBase
{
public:
	virtual ~StateBase() = default;
	virtual void Enter(Player& player){};
	virtual void Update(Player& player) = 0;
	virtual void Exit(Player& player) {};
};
/// <summary>
/// Idle状態のクラス
/// </summary>
class Idle : public StateBase
{
	public:
	void Update(Player& player) override;
};
/// <summary>
/// Move状態のクラス
/// </summary>
class Move : public StateBase
{
public:
	void Update(Player& player) override;
};
/// <summary>
/// Jamp状態のクラス
/// </summary>
class Jump : public StateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player) override;
};

