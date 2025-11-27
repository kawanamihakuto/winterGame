#pragma once
#include"Geometry.h"
#include"Collision/Rect.h"
/// <summary>
/// ゲーム全体のオブジェクト基底クラス
/// </summary>
class GameObject
{
public:
	GameObject(const Vector2 pos );
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual bool CheckCollision(const Rect& other)const = 0;
	virtual void OnHit(Rect* other) = 0;
protected:
	Vector2 position_;
	Rect rect_;
};

