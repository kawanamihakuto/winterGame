#pragma once
#include "BossBase.h"
class SunBoss : public BossBase
{
public:
	SunBoss(Vector2 pos,int graphHandle,std::shared_ptr<Player>player,std::shared_ptr<EffectManager>effectManager);
	~SunBoss();
	void Init();
	void Init(int stageNo)override;
	void Update() override;
	void Draw() override;
	void Draw(Camera& camera) override;

	void ChangeState(std::unique_ptr<BossState::BossStateBase> newState)override;
private:
	int actionIntervalCount_;
	//sinfópframeïœêî
	float sinFrame_;

	int deadCount_;
};

