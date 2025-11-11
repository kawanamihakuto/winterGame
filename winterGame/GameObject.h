#pragma once
#include"Geometry.h"
#include"Rect.h"
/// <summary>
/// ゲーム全体のオブジェクト基底クラス
/// </summary>
class GameObject
{
public:
	GameObject(const Vector2 pos);
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

protected:
	Vector2 position_;
	Rect rect_;
};

