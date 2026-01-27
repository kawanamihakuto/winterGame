#pragma once
class GameSceneUI
{
public:
	GameSceneUI(int backToTitleGraphHandle);
	~GameSceneUI();
	void Init();
	void Update();
	void Draw();
private:
	int backToTitleGraphHandle_;
};

