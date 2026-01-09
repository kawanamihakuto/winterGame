#pragma once
#include "Scene.h"
class ClearScene :public Scene
{
public:
	ClearScene(SceneController& controller);
	void Update(Input&)override;
	void Draw()override;
};

