#pragma once
#include"../Base/GameObject.h"
#include<memory>
#include<vector>
class Player;
class EnemyBase;
class Camera;
class Shot :public GameObject
{
public:
	Shot(Vector2 pos,int graphHandle);
	virtual ~Shot();

	void Init()override = 0;
	virtual void Init(std::shared_ptr<Player>player) = 0;
	void Update()override = 0;
	virtual void Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies) = 0;
	void Draw()override = 0;
	virtual void Draw(Camera& camera) = 0;

	bool GetIsActive() { return isActive_; }
	void SetIsActive(bool isActive) { isActive_ = isActive; }
protected:
	Vector2 velocity_;
	int graphHandle_;
	bool isRight_;
	bool isActive_;
};

