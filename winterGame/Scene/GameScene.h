#pragma once
#include "Scene.h"
#include<memory>
#include<vector>
#include"../Player/Player.h"
#include"../Actor/WalkEnemy.h"
class Player;
class EnemyBase;
class Inhale;
class Camera;
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

	//プレイヤーのポインタ
	std::shared_ptr<Player>player_;
	//エネミーのポインタ
	std::vector<std::shared_ptr<EnemyBase>>enemies_;
	//吸い込みオブジェクトのポインタ
	std::shared_ptr<Inhale>inhale_;
	//カメラのポインタ
	std::shared_ptr<Camera>camera_;


	//プレイヤーの画像構造体
	PlayerImages playerImgs_;
	//敵の画像構造体
	EnemyImages EnemyImgs_;
public:
	//コンストラクタ
	GameScene(SceneController& controller);
	~GameScene();
	void Update(Input&)override;
	void Draw()override;
};