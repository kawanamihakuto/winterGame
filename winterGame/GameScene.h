#pragma once
#include "Scene.h"
#include<memory>
#include"Player.h"
#include"WalkEnemy.h"
class Player;
class WalkEnemy;
/// <summary>
/// ゲームシーンクラス
/// </summary>
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

	std::unique_ptr<Player>player_;
	std::shared_ptr<WalkEnemy>walkEnemy_;
private:
	

public:
	//コンストラクタ
	GameScene(SceneController& controller);
	
	void Update(Input&)override;
	void Draw()override;

	int playerIdleH_;

	int enemyWalkH_;
};

