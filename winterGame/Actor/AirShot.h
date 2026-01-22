#pragma once
#include "Base/Shot.h"
#include<memory>

class EffectManager;
class AirShot :public Shot
{
public:
	AirShot(bool isRight,Vector2 pos, int graphHandle,std::shared_ptr<EffectManager>effectManager);
	virtual ~AirShot();

	void Init()override;
	void Init(std::shared_ptr<Player>player)override;
	void Update()override;
	void Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies,Stage& stage)override;
	void Draw()override;
	void Draw(Camera& camera)override;
private:
	//¶‚«‚Ä‚¢‚éŠÔ‚ÌƒJƒEƒ“ƒg
	int count_;
};

