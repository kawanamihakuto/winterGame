#pragma once
#include "EnemyBase.h"
class FlyEnemy :public EnemyBase
{
public:
	FlyEnemy(Vector2 pos, int graphHandle, std::shared_ptr<Player>player);
	~FlyEnemy();
	void Init()override;
	void Update() override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<EnemyStateBase>);
	Vector2 GetPosition() const { return position_; }
private:
};

///// <summary>
///// Move状態クラス
///// </summary>
//class Move : public EnemyStateBase
//{
//	void Enter(EnemyBase& enemy)override;
//	void Update(EnemyBase& enemy)override;
//	void Exit(EnemyBase& enemy)override;
//};
//
///// <summary>
///// Death状態クラス
///// </summary>
//class Death : public EnemyStateBase
//{
//	void Enter(EnemyBase& enemy) override;
//	void Update(EnemyBase& enemy) override;
//	void Exit(EnemyBase& enemy) override;
//};
//
///// <summary>
///// None状態クラス
///// (画面外状態)
///// </summary>
//class None : public EnemyStateBase
//{
//	void Enter(EnemyBase& enemy) override;
//	void Update(EnemyBase& enemy) override;
//	void Exit(EnemyBase& enemy) override;
//};
//
///// <summary>
///// 吸い込まれている状態クラス
///// </summary>
//class Inhaled : public EnemyStateBase
//{
//	void Enter(EnemyBase& enemy) override;
//	void Update(EnemyBase& enemy) override;
//	void Exit(EnemyBase& enemy) override;
//};
