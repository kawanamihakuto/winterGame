#pragma once
#include "../Base/GameObject.h"
#include<memory>
#include<vector>
class EnemyBase;
class Player;
class Camera;
class Inhale :public GameObject
{
public:
	Inhale(Vector2 pos);
	~Inhale();

	void Init()override;
	void Update()override;
	void Update(std::shared_ptr<Player>player,std::vector<std::shared_ptr<EnemyBase>>enemies);
	void Draw()override;
	void Draw(Camera& camera);

	Vector2 Vlerp(const Vector2 stert, const Vector2 end, float t);
};

