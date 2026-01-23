#pragma once
#include "Scene.h"
class GameoverScene :public Scene
{
public:
	GameoverScene(SceneController& controller,int stageNo);
	~GameoverScene();

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
	using UpdateFunc_t = void(GameoverScene::*)(Input&);
	UpdateFunc_t update_;

	//通常Draw
	void NormalDraw();
	//フェードDraw
	void FadeDraw();
	//Drawメンバ関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(GameoverScene::*)();
	DrawFunc_t draw_;

	void Update(Input&)override;
	void Draw()override;
private:
	int stageNo_;
	int gameoverGraphHandle_;
	bool isFadeInOrFadeOut_;
	int count_;
};

