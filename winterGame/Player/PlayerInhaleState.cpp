#include "PlayerInhaleState.h"
#include"Player.h"
#include"../System/Input.h"
#include"PlayerIdleState.h"

void PlayerInhaleState::Enter(Player& player)
{
	//画像をInhaleに変更
	player.SetGraph(player.GetImages().inhale);
	//吸い込みオブジェクトの生成をリクエストする
	player.SetGenerateInhale(true);
	//横方向のvelocityを0にする
	player.SetVelocity({ 0.0f,player.GetVelocity().y });
}

void PlayerInhaleState::Update(Player& player, Input& input)
{
	//ボタンを離したら吸い込みを終わる
	if (!input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<PlayerIdleState>());
	}

	player.UpdatePhysics();
}

void PlayerInhaleState::Exit(Player& player)
{
	//吸い込みオブジェクトの削除をリクエストする
	player.SetDeleteInhale(true);
}