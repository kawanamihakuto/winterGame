#pragma once
#include "Base/GameObject.h"
#include<memory>
#include<vector>
class EnemyBase;
class Player;
class Camera;
class Inhale :public GameObject
{
public:
	Inhale(Vector2 pos,int graphHandle);
	~Inhale();

	void Init()override;
	void Init(std::shared_ptr<Player>player);
	void Update()override;
	void Update(std::shared_ptr<Player>player,std::vector<std::shared_ptr<EnemyBase>>enemies);
	void Draw()override;
	void Draw(Camera& camera);

	bool GetIsActive() { return isActive_; }
	void SetIsActive(bool isActive) { isActive_ = isActive; }
private:
	bool isActive_;
	bool isRight_;
	int graphHandle_;
};

