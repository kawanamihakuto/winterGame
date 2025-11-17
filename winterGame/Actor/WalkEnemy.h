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
	std::unique_ptr<EnemyStateBase> state_;

	WalkEnemy(Vector2 pos,EnemyImages& imgs,std::shared_ptr<Player>player);
	~WalkEnemy ();
	void Init()override;
	void Update() override;
	void Draw() override;

	Vector2 GetPosition() const { return position_; }
private:
	//画像ハンドルをまとめて持つ
	EnemyImages images_;
	
};