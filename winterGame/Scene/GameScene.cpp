#include "GameScene.h"
#include<DxLib.h>
#include"SceneController.h"
#include"../Application.h"
#include"../System/Input.h"
#include"GameoverScene.h"
#include"../Actor/Player.h"
#include"../Actor/WalkEnemy.h"
//フェードにかかるフレーム数
constexpr int fade_interval = 60;

GameScene::GameScene(SceneController& controller) :Scene(controller),
update_(&GameScene::FadeInUpdate),
draw_(&GameScene::FadeDraw)
{
	//idle
	//move
	//jump
	playerImgs_ = 
	{
		LoadGraph("data/player/Idle.png"),
		LoadGraph("data/player/Move.png"),
		LoadGraph("data/player/Jump.png")
	};

	//walk
	walkEnemyImgs_ = 
	{
		LoadGraph("data/walkEnemy/Walk.png"),
		LoadGraph("data/walkEnemy/Death.png")
	};

	player_ = std::make_shared<Player>(playerImgs_);
	std::shared_ptr<WalkEnemy> we = std::make_shared<WalkEnemy>(Vector2{ 600,200 }, walkEnemyImgs_, player_);
	enemies_.push_back(we);
	frame_ = fade_interval;	
}

GameScene::~GameScene()
{
	
	DeleteGraph(playerImgs_.idle);
	DeleteGraph(playerImgs_.move);
	DeleteGraph(playerImgs_.jump);
	
	DeleteGraph(walkEnemyImgs_.walk);
	DeleteGraph(walkEnemyImgs_.death);
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
	player_->Update(input);
	for (auto& enemy : enemies_)
	{
		enemy->Update();
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

	player_->Draw();
	for (auto& enemy : enemies_)
	{
		enemy->Draw();
	}
}

void GameScene::Update(Input& input)
{
	(this->*update_)(input);
}

void GameScene::Draw()
{
	(this->*draw_)();
}