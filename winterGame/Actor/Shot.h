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
	~Shot();

	void Init()override;
	void Init(std::shared_ptr<Player>player);
	void Update()override;
	void Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies);
	void Draw()override;
	void Draw(Camera& camera);

	bool GetIsActive() { return isActive_; }
	void SetIsActive(bool isActive) { isActive_ = isActive; }
private:
	Vector2 velocity_;
	int graphHandle_;
	bool isRight_;
	int GraphCutNo_;
	bool isActive_;
};

