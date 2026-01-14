#pragma once
#include"Geometry.h"
class Player;
class Camera;
class PlayerHPUI
{
	public:
	PlayerHPUI(int GraphHandle);
	~PlayerHPUI();
	void Init();
	void Update();
	void Draw(Player& player);
private:
	Vector2 position_;
	int graphHandle_;
};

