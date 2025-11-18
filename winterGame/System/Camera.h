#pragma once
#include"../base/GameObject.h"
class Player;
class Camera :public GameObject
{
public:
	Camera();
	~Camera();

	void Init();
	void Init(Player& player);
	void Update();
	void Update(Player& player);
	void Draw();

	//DrawOffsetÇÃÉQÉbÉ^Å[
	Vector2 GetDrawOffset() { return drawOffset_; }

	Vector2 VLerp(const Vector2& stert, const Vector2& end, float t);

private:
	Vector2 drawOffset_;
};

