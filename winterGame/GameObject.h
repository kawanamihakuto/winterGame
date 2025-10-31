#pragma once
#include"Geometry.h"
class GameObject
{
public:
	GameObject(const Vector2 pos);
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Vector2 position_;
};

