#pragma once
#include "Base/EnemyBase.h"
#include <memory>

class WalkEnemyStateBase;
class EnemyStateBase;
class Player;
class Camera;
class Stage;
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
	void Update(Stage& stage,Camera& camera)override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<EnemyStateBase>newState);
	Vector2 GetPosition() const { return position_; }

	/// <summary>
	/// X方向のマップとの衝突判定
	/// </summary>
	/// <param name="stage">stage情報</param>
	void MapCollisionX(const Stage& stage, Rect tileRect);
	/// <summary>
	/// Y方向のマップとの衝突判定
	/// </summary>
	/// <param name="stage">stage情報</param>
	void MapCollisionY(const Stage& stage, Rect tileRect);

private:
};

