#pragma once
#include "../Base/GameObject.h"
class Inhale :public GameObject
{
public:
	Inhale();
	~Inhale();

	void Init()override;
	void Update()override;
	void Draw()override;
};

