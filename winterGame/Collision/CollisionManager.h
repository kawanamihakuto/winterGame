#pragma once
#include<vector>
class Rect;
class CollisionManager
{
public:
	void Add(Rect* rect);

	void Clear();


		 
private:
	std::vector<Rect*> colliders_;
};