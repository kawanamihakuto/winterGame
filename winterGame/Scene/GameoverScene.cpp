#include "GameoverScene.h"
#include<DxLib.h>
#include"Input.h"
#include"TitleScene.h"
#include"SceneController.h"
#include"Application.h"
#include"GameScene.h"
#include<cassert>
GameoverScene::GameoverScene(SceneController& controller,int stageNo) :Scene(controller),
stageNo_(stageNo)
{
	gameoverGraphHandle_ = LoadGraph("data/Gameover.png");
	assert(gameoverGraphHandle_ > -1);
}

GameoverScene::~GameoverScene()
{
	DeleteGraph(gameoverGraphHandle_);
}

void GameoverScene::Update(Input& input)
{
	if (input.IsTriggered("ok"))
	{
		if (stageNo_ == 1)
		{
			controller_.ChangeScene(std::make_shared<GameScene>(controller_,stageNo_));
			return;
		}
		else if (stageNo_ == 2)
		{
			controller_.ChangeScene(std::make_shared<GameScene>(controller_, stageNo_));
			return;
		}
		else if (stageNo_ == 3)
		{
			controller_.ChangeScene(std::make_shared<GameScene>(controller_, stageNo_));
			return;
		}
	}
}
void GameoverScene::Draw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w*0.5f, wsize.h*0.5f, "GameoverScene",0xffffff);
}
