#pragma once
#include "../Base/EnemyBase.h"
#include <memory>

class WalkEnemy;
class WalkEnemyStateBase;
class EnemyStatebase;
class Rect;
class Player;
class Camera;
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
//	std::unique_ptr<WalkEnemyStateBase> state_;

	WalkEnemy(Vector2 pos,EnemyImages& imgs,std::shared_ptr<Player>player);
	~WalkEnemy ();
	void Init()override;
	void Update() override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<EnemyStateBase>newState);
	Vector2 GetPosition() const { return position_; }
private:
	//画像ハンドルをまとめて持つ
	EnemyImages images_;
	
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

