#pragma once
#include "Scene.h"
class ClearScene :public Scene
{
public:
	ClearScene(SceneController& controller);
	~ClearScene();
	void Update(Input&)override;
	void Draw()override;

	//フェードインUpdate
	void FadeInUpdate(Input&);
	//通常Update
	void NormalUpdate(Input&);
	//フェードアウトUpdate
	void FadeOutUpdate(Input&);
	//Updateメンバ関数を代入できるメンバ関数ポインタ
	using UpdateFunc_t = void(ClearScene::*)(Input&);
	UpdateFunc_t update_;

	//フェードDraw
	void FadeDraw();
	//通常Draw
	void NormalDraw();
	//Draw関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(ClearScene::*)();
	DrawFunc_t draw_;

private:
	int EffectHandle_;

	int bgHandle_;

	int gameClearGraphHandle_;

	int nowEffect_;

	int count_;

	int frame_;

	int gameGraphHandle_;

	bool isFadeInOrFadeOut_;

	float playerFadePosX_;

	int playerSrcX_;

	int playerCount_;

	//PressStartグラフハンドル
	int pressStartGraphHandle_;
	//PressStartを表示するまでの待機時間カウンター
	int pressStartWaitingCount_;

	int pressStartFadeCount_;
};

