#pragma once
#include "BossBase.h"
class SunBoss : public BossBase
{
public:
	SunBoss(Vector2 pos);
	~SunBoss();
	void Init()override;
	void Update() override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<BossStateBase> newState)override;
};

