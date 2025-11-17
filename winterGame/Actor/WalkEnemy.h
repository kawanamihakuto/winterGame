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

	//imagesのゲッター
	const WalkEnemyImages& GetImages() const { return images_; }

	/// <summary>
	/// 重力用関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// 移動を適用する関数
	/// </summary>
	void ApplyMovement();
	Vector2 GetPosition() const { return position_; }
private:
	//画像ハンドルをまとめて持つ
	WalkEnemyImages images_;
	
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