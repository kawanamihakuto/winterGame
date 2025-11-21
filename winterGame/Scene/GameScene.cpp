#include "GameScene.h"
#include<DxLib.h>
#include"SceneController.h"
#include"../Application.h"
#include"../System/Input.h"
#include"GameoverScene.h"
#include"../Player/Player.h"
#include"../Actor/WalkEnemy.h"
#include<cassert>
#include"../Actor/Inhale.h"
#include"../System/Camera.h"
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw)
{

	graphHandle_ = LoadGraph("data/kirby.png");
	assert(graphHandle_ > -1);
	//プレイヤーの画像をロード
	//idle
	//move
	//jump
	//inhale(吸い込み)
	//mouthHoldIdle
	//mouthHoldMove;
	playerImgs_ = 
	{
		LoadGraph("data/player/Idle.png"),
		LoadGraph("data/player/Move.png"),
		LoadGraph("data/player/Jump.png"),
		LoadGraph("data/player/Inhale.png"),
		LoadGraph("data/player/MouthHoldIdle.png"),
		LoadGraph("data/player/MouthHoldMove.png"),
		LoadGraph("data/player/MouthHoldJump.png")
	};
	assert(playerImgs_.idle>-1);
	assert(playerImgs_.move>-1);
	assert(playerImgs_.jump>-1);
	assert(playerImgs_.inhale>-1);
	assert(playerImgs_.mouthHoldIdle>-1);
	assert(playerImgs_.mouthHoldMove>-1);
	assert(playerImgs_.mouthHoldJump>-1);
	//歩くエネミーの画像をロード
	//walk
	//Death
	EnemyImgs_ = 
	{
		LoadGraph("data/walkEnemy/Walk.png"),
		LoadGraph("data/walkEnemy/Death.png"),
		LoadGraph("data/walkEnemy/Inhaled.png")
	};
	assert(EnemyImgs_.walk_walk>-1);
	assert(EnemyImgs_.walk_death>-1);
	assert(EnemyImgs_.walk_inhaled>-1);

	//プレイヤー生成
	player_ = std::make_shared<Player>(graphHandle_);
	//歩く敵生成
	std::shared_ptr<WalkEnemy> we = std::make_shared<WalkEnemy>(Vector2{ 600,200 }, EnemyImgs_, player_);
	enemies_.push_back(we);

	camera_ = std::make_shared<Camera>();
	//フェード用のフレームを初期化
	frame_ = fade_interval;	
}

GameScene::~GameScene()
{
	//画像をすべてデリート
	DeleteGraph(graphHandle_);
	//プレイヤー
	DeleteGraph(playerImgs_.idle);
	DeleteGraph(playerImgs_.move);
	DeleteGraph(playerImgs_.jump);
	DeleteGraph(playerImgs_.inhale);
	DeleteGraph(playerImgs_.mouthHoldIdle);
	DeleteGraph(playerImgs_.mouthHoldMove);
	DeleteGraph(playerImgs_.mouthHoldJump);
	//歩く敵
	DeleteGraph(EnemyImgs_.walk_walk);
	DeleteGraph(EnemyImgs_.walk_death);
	DeleteGraph(EnemyImgs_.walk_inhaled); 
}

void GameScene::FadeInUpdate(Input&)
{
	//フェードインが終わったら状態を切り替える
	if (--frame_ <= 0)
	{
		update_ = &GameScene::NormalUpdate;
		draw_ = &GameScene::NormalDraw;
		return;
	}
}

void GameScene::NormalUpdate(Input& input)
{
	//プレイヤーのUpdate
	player_->Update(input);
	//エネミー全体のUpdate
	for (auto& enemy : enemies_)
	{
		enemy->Update();
	}

	camera_->Update(*player_);
	//吸い込みオブジェクトの生成処理
	if (player_->GetGenerateInhale())
	{
		printfDx("new\n");
		//吸い込みオブジェクト生成
		inhale_ = std::make_shared<Inhale>(player_->GetPosition());
		player_->SetGenerateInhale(false);
	}

	//吸い込みオブジェクトがあったら
	if (inhale_)
	{
		//吸い込みオブジェクトのUpdate
		inhale_->Update(player_, enemies_);
	}
	
	//remove_ifで消すべき要素を後ろに詰める
	auto newEnd = std::remove_if(
		enemies_.begin(),//vectorの最初の要素
		enemies_.end(),//vectorの最後の'次'の要素(end()に到達したらループ終了する)
		[](const std::shared_ptr<EnemyBase>& enemy)//ラムダ式(引数にremove_ifで現在の要素を渡す)
		{
			//死んでいるかどうかのフラグをチェック
			return enemy->GetIsDead();
		});
	//remove_ifで後ろに詰められた要素を消す
	enemies_.erase(newEnd, enemies_.end());

	//吸い込みオブジェクトの削除
	if (player_->GetDeleteInhale())
	{
		printfDx("delete\n");
		inhale_.reset();
		player_->SetDeleteInhale(false);
	}

	//ボタンが押されたらフェードアウトを始める
	if (input.IsTriggered("ok"))
	{
		update_ = &GameScene::FadeOutUpdate;
		draw_ = &GameScene::FadeDraw;
	}
}

void GameScene::FadeOutUpdate(Input&)
{
	//フェードアウトし終わったらシーンを切り替える
	if (++frame_ >= fade_interval)
	{
		controller_.ChangeScene(std::make_shared<GameoverScene>(controller_));
		return;
	}
}

void GameScene::FadeDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);
	//フェード処理
	float rate = static_cast<float>(frame_) / static_cast<float>(fade_interval);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * rate);
	DrawBox(0, 0, wsize.w, wsize.h, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255 * rate);
}

void GameScene::NormalDraw()
{
	//ウィンドウサイズ取得
	const auto& wsize = Application::GetInstance().GetWindowSize();
	DrawString(wsize.w * 0.5f, wsize.h * 0.5f, "GameScene", 0xffffff);

	//プレイヤーのDraw
	player_->Draw(*camera_);
	//エネミー全体のDraw
	for (auto& enemy : enemies_)
	{
		enemy->Draw(*camera_);
	}
	//吸い込みオブジェクトがあったら
	if (inhale_)
	{
		//吸い込みオブジェクトのDraw
		inhale_->Draw(*camera_);
	}
}

void GameScene::Update(Input& input)
{
	//現在のUpdateを実行
	(this->*update_)(input);
}

void GameScene::Draw()
{
	//現在のDrawを実行
	(this->*draw_)();
}