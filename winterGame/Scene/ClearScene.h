#pragma once
#include "Scene.h"
class ClearScene :public Scene
{
public:
	ClearScene(SceneController& controller);
	~ClearScene();
	void Update(Input&)override;
	void Draw()override;

private:
	int EffectHandle_;

	int nowEffect_;

	int frame_;
};

