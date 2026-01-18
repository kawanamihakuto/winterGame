#pragma once
#include<memory>
#include<vector>
#include"Application.h"
struct Effect
{
	Vector2 pos;
	int frame = 0;
	bool isAlive = true;
	double angle;
	double size;
}; 
class Camera;
class EffectManager
{
public:
	EffectManager(int graphHandle);
	~EffectManager();
	void Init();
	void Update();
	void Draw(Camera& camera);

	void Generate(const Vector2& pos);
private:
	std::vector<std::shared_ptr<Effect>>effects_;
	int graphHandle_;
};

