#pragma once
#include"Geometry.h"
class BossBase;
class BossHPUI
{
public:
	BossHPUI(int graphHandle,int textHandle);
	~BossHPUI();
	void Init();
	void Update();
	void Draw();
	void Draw(BossBase& boss);
private:
	Vector2 position_;
	int hpGraphHandle_;
	int textGraphHandle_;
};

