#pragma once
#include "Scene.h"
#include<memory>
#include<vector>
#include"CollisionManager.h"
class Stage;
class TileMapRenderer;
class Player;
class EnemyBase;
class Inhale;
class Camera;
class Shot;
class PlayerInhaledRect;
class Door;
class PlayerHPUI;
class UIFrame;
class Bg;
/// <summary>
/// ゲームシーンクラス
/// </summary>
class GameScene :public Scene
{
public:
	//コンストラクタ
	GameScene(SceneController& controller);
	~GameScene();
	void Update(Input&)override;
	void Draw()override;
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
	//ステージデータ
	std::unique_ptr<Stage>stage_;
	//マップチップ描画
	std::shared_ptr<TileMapRenderer>mapRenderer_;
	//プレイヤーのポインタ
	std::shared_ptr<Player>player_;
	//エネミーのポインタ
	std::vector<std::shared_ptr<EnemyBase>>enemies_;
	//吸い込みオブジェクトのポインタ
	std::shared_ptr<Inhale>inhale_;
	//吸い込み中に出す当たり判定のポインタ
	std::shared_ptr<PlayerInhaledRect>playerInhaledRect_;
	//カメラのポインタ
	std::shared_ptr<Camera>camera_;
	//弾のポインタ
	std::vector<std::shared_ptr<Shot>>shots_;
	//ドアのポインタ
	std::shared_ptr<Door>door_;
	//プレイヤーのHPUIのポインタ
	std::shared_ptr<PlayerHPUI>playerHPUI_;
	//UIフレームのポインタ
	std::shared_ptr<UIFrame>UIFrame_;
	//背景のポインタ
	std::shared_ptr<Bg>Bg_;

	//当たり判定を行うCollisionManager
	CollisionManager collisionManager_;
	//プレイヤー、敵、地形の画像ハンドル
	int graphHandle_;
	//プレイヤーのHp画像ハンドル
	int playerHpGraphHandle_;
	//UIフレーム画像ハンドル
	int UIFrameGraphHandle_;
	//背景(空)の画像ハンドル
	int skyGraphHandle_;
	//背景(雲)の画像ハンドル
	int cloudGraphHandle_;
	//背景(太陽)の画像ハンドル
	int sunGraphHandle_;
};