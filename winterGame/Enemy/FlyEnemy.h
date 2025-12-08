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
