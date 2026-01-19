#pragma once
#include "Scene.h"
/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene :public Scene
{
private:
	//経過フレーム
	int frame_;

	//<メンバ関数ポインタで内部状態を切り替える>
	//フェードインUpdate
	void FadeInUpdate(Input&);
	//通常Update
	void NormalUpdate(Input&);
	//フェードアウトUpdate
	void FadeOutUpdate(Input&);

	//Updateメンバ関数を代入できるメンバ関数ポインタ
	using UpdateFunc_t = void(TitleScene::*)(Input&);
	UpdateFunc_t update_;

	//通常Draw
	void NormalDraw();
	//フェードDraw
	void FadeDraw();
	//Drawメンバ関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(TitleScene::*)();
	DrawFunc_t draw_;

	//タイトルグラフハンドル
	int titleGraphHandle_;
	//PressStartグラフハンドル
	int pressStartGraphHandle_;
	//背景グラフハンドル
	int bgHandle_;

	int count_;

	bool isFadeInOrFadeOut_;
public:
	TitleScene(SceneController& controller);
	~TitleScene();
	void Update(Input&)override;
	void Draw()override;
};

