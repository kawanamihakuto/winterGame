#include "InhaleState.h"
#include"Player.h"
#include"Input.h"
#include"IdleState.h"
#include"InhaleHoldState.h"
#include<memory>
#include"GameScene.h"
void PlayerState::InhaleState::Enter(Player& player)
{
	//画像をInhaleに変更
	player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthOpen);
	//吸い込みオブジェクトの生成をリクエストする
	player.StartInhale();
	player.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"inhale",true });
}

void PlayerState::InhaleState::Update(Player& player, Input& input)
{
	//ボタンを離したら吸い込みを終わる
	if (!input.IsPressed("attack"))
	{
		player.GetScene()->PushRequest({ SceneRequestType::StopSE,0.0f,0,"inhale"});
		player.ChangeState(std::make_unique<IdleState>());
		player.EndInhale();
	}
	//吸い込み状態の継続がtrueになったら
	if (player.GetIsInhaledHold())
	{
		//吸い込み継続状態にする
		player.ChangeState(std::make_unique<PlayerState::InhaleHoldState>());
	}
}

void PlayerState::InhaleState::Exit(Player& player)
{
	
}