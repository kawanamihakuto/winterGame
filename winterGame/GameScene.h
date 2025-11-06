#pragma once
#include "Scene.h"
class GameScene :public Scene
{
private:
	//フェードインアウト用
	int frame_ = 0;
	//ゲーム中のフレームをカウント
	int gameFrame_ = 0;
	//フェードインUpdate
	void FadeInUpdate(Input&);
	//通常Update
	void NormalUpdate(Input&);
	//フェードアウトUpdate
	void FadeOutUpdate(Input&);
	//Updateメンバ関数を代入できるメンバ関数ポインタ
	using UpdateFunc_t = void(GameScene::*)(Input&);
	UpdateFunc_t update_;

	//フェードDraw
	void FadeDraw();
	//通常Draw
	void NormalDraw();
	//Draw関数を代入できるメンバ関数ポインタ
	using DrawFunc_t = void(GameScene::*)();
	DrawFunc_t draw_;

public:
	//コンストラクタ
	GameScene(SceneController& controller);
	
	void Update(Input&)override;
	void Draw()override;

	int playerIdleH_;
};

