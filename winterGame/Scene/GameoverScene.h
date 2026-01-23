#pragma once
#include "Scene.h"
class GameoverScene :public Scene
{
public:
	GameoverScene(SceneController& controller,int stageNo);
	~GameoverScene();
	void Update(Input&)override;
	void Draw()override;
private:
	int stageNo_;
	int gameoverGraphHandle_;
};

