#pragma once
#include"Geometry.h"
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Vector2 posX_;
	Vector2 posY_;
};

