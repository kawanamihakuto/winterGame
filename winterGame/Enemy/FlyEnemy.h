#pragma once
#include "EnemyBase.h"
class Stage;
class FlyEnemy :public EnemyBase
{
public:
	FlyEnemy(Vector2 pos, int graphHandle, std::shared_ptr<Player>player,std::shared_ptr<EffectManager>effectManager,bool isRight);
	~FlyEnemy();
	void Init()override;
	void Update() override;
	void Update(Stage& stage,Camera& camera) override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<EnemyStateBase>);
	Vector2 GetPosition() const { return position_; }
private:
};
