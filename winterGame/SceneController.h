#pragma once
#include<memory>
#include<list>
class Input;
class Scene;
/// <summary>
/// シーンを内部に保持し、切り替える
/// </summary>
class SceneController
{
private:
	//現在スタックに積まれているシーン
	//最後に積んだものがUpdateされる
	std::list<std::shared_ptr<Scene>>scenes_;
public:
	/// <summary>
	/// シーンの切り替え
	/// </summary>
	/// <param name="scene">新しいシーン</param>
	/// <note>最後に積んだシーンがChangeされる</note>
	void ChangeScene(std::shared_ptr<Scene>scene);
	/// <summary>
	/// シーンを新しくスタックに積む
	/// </summary>
	/// <param name="scene">積みたいシーン</param>
	/// <note>ChangeSceneと違ってもともと積まれてるシーンは残る</note>
	void PushScene(std::shared_ptr<Scene>scene);
	/// <summary>
	/// 最後に積んだシーンをリストから外す
	/// </summary>
	void PopScene();
	/// <summary>
	/// 内部に持っているシーンのUpdateを呼び出す
	/// </summary>
	/// <param name="input"></param>
	void Updarte(Input& input);
	/// <summary>
	/// 内部に持っているシーンのDrawを呼び出す
	/// </summary>
	void Draw();
};

