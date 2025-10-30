#include "SceneController.h"
#include"Scene.h"

void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
{
	//最初にemptyかどうかのチェック
	if (scenes_.empty())
	{
		//最初は要素がないからPush_backする
		scenes_.push_back(scene);
	}
	//シーンの切り替え
	//元あったシーンは自動的に削除される
	scenes_.back() = scene;
}

void SceneController::PushScene(std::shared_ptr<Scene> scene)
{
	//新しいシーンを末尾に積む
	scenes_.push_back(scene);
}

void SceneController::PopScene()
{
	//末尾のシーンを削除
	scenes_.pop_back();
}

void SceneController::Update(Input& input)
{
	//末尾のシーンのみ、Updateを行う
	scenes_.back()->Update(input);
}

void SceneController::Draw()
{
	//Drawはすべて行う
	for (auto& scene : scenes_)
	{
		scene->Draw();
	}
}
