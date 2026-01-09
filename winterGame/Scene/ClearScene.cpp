#include "ClearScene.h"
#include"Input.h"
#include"TitleScene.h"
#include"Application.h"
#include"SceneController.h"
#include<DxLib.h>
ClearScene::ClearScene(SceneController& controller):Scene(controller)
{
}

void ClearScene::Update(Input& input)
{
	if (input.IsTriggered("ok"))
	{
		controller_.ChangeScene(std::make_shared<TitleScene>(controller_));
		return;
	}
}

void ClearScene::Draw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "ClearScene", 0xffffff);
}
