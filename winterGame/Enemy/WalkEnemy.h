#pragma once
#include "Base/EnemyBase.h"
#include <memory>

class WalkEnemy;
class WalkEnemyStateBase;
class EnemyStatebase;
class Rect;
class Player;
class Camera;

/// <summary>
/// 歩く敵クラス
/// </summary>
class WalkEnemy :public EnemyBase
{
public:
	WalkEnemy(Vector2 pos,int graphHandle,std::shared_ptr<Player>player);
	~WalkEnemy ();
	void Init()override;
	void Update() override;
	void Draw() override;
	void Draw(Camera& camera) override;

	//マップタイルと当たった時の処理を行う関数
	void OnCollisionTile(const Rect& tileRect)override;

	void ChangeState(std::unique_ptr<EnemyStateBase>newState);
	Vector2 GetPosition() const { return position_; }

private:
};

