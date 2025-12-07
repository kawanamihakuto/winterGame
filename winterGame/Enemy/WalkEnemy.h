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
/// •à‚­“GƒNƒ‰ƒX
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

	void ChangeState(std::unique_ptr<EnemyStateBase>newState);
	Vector2 GetPosition() const { return position_; }

private:
};

