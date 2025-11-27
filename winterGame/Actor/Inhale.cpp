#include "Inhale.h"
#include<memory>
#include<vector>
#include"Collision/Rect.h"
#include"Player.h"
#include"Base/EnemyBase.h"
#include<DxLib.h>
#include"Camera.h"
#include"WalkEnemy.h"
#include"Lerp.h"
#include"InhaleHoldState.h"
#include "Base/Shot.h"
//吸い込み範囲の幅
constexpr int kWidth = 32;
//吸い込み範囲の高さ
constexpr int kHeight = 32;
//吸い込み範囲の拡大倍率
constexpr int kSize = 2;
//プレイヤーからのoffsetX
constexpr int kOffsetX = 48;
//吸い込むときのLerpのtの値
constexpr float kInhaleLerpT = 0.05f;

Inhale::Inhale(Vector2 pos,int graphHandle) : GameObject(pos),
	isActive_(false),
	graphHandle_(graphHandle),
	isRight_(false)
{
}

Inhale::~Inhale()
{
}

void Inhale::Init()
{
	
}
void Inhale::Init(std::shared_ptr<Player>player)
{
	isActive_ = true;
	//プレイヤーのpositionを取得
	Vector2 playerPos = player->GetPosition();

	bool isPlayerRight = player->GetIsRight();
	//プレイヤーが右を向いていたら
	if (isPlayerRight)
	{
		isRight_ = true;
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして右に出す
		position_.x = playerPos.x + kOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		isRight_ = false;
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = player->GetPosition().y;

}
void Inhale::Update()
{
}

void Inhale::Update(std::shared_ptr<Player>player,std::vector<std::shared_ptr<EnemyBase>>enemies)
{
	//プレイヤーのpositionを取得
	Vector2 playerPos = player->GetPosition();

	bool isPlayerRight = player->GetIsRight();
	//プレイヤーが右を向いていたら
	if (isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして右に出す
		position_.x = playerPos.x + kOffsetX;
	}
	//プレイヤーが左を向いていたら
	if (!isPlayerRight)
	{
		//吸い込みのpositionをプレイヤーからoffsetX分ずらして左に出す
		position_.x = playerPos.x - kOffsetX;
	}
	//プレイヤーの高さに合わせる
	position_.y = playerPos.y;
	if (isActive_)
	{
		//プレイヤーの吸い込み状態の継続をいったんfalseにする
		player->SetIsInhaledHold(false);
		Lerp lerp;
		for (auto& enemies : enemies)
		{
			//すべてのエネミーとの当たり判定をチェック
			if (rect_.IsCollision(enemies->GetHitRect()))
			{
				//1体でもエネミーが吸い込み範囲にいたら
				// プレイヤーに吸い込み状態を継続させる
				player->SetIsInhaledHold(true);
				//エネミーのステートを変更
				enemies->ChangeState(std::make_unique<Inhaled>());
				//吸い込まれている敵の挙動をLerpで実装
				enemies->SetPosition(lerp.VLerp(enemies->GetPosition(), player->GetPosition(), kInhaleLerpT));
			}
		}
	}
}

void Inhale::Draw()
{
	
	
}

void Inhale::Draw(Camera& camera)
{
	if (isActive_)
	{
		DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight * 0.5f) + camera.GetDrawOffset().y,
			16 * 3, 0, kWidth, kHeight, kSize, 0, graphHandle_,true, !isRight_);
	}
#ifdef _DEBUG
	//当たり判定を可視化
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight * 0.3f) + camera.GetDrawOffset().y, kWidth, kHeight);
	rect_.Draw(0x00ffff, false);
#endif // _DEBUG
}


