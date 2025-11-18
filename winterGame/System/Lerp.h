#pragma once
#include"Geometry.h"
class Lerp
{
public:
	Lerp();
	~Lerp();
	Vector2 VLerp(const Vector2 stert, const Vector2 end, float t);
};

