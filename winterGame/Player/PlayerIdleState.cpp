#include "PlayerIdleState.h"
#include"Player.h"
#include"../System/Input.h"
#include"PlayerMoveState.h"
#include"PlayerInhaleState.h"
#include"PlayerJumpState.h"
void PlayerIdleState::Enter(Player& player)
{
	//画像をIdleに変更 
	player.SetGraph(player.GetImages().idle);
	// velocityを0にする
	player.SetVelocity({ 0.0f,0.0f });
}

void PlayerIdleState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//左の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<PlayerMoveState>());
	}
	//右の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<PlayerMoveState>());
	}
	//ジャンプ入力が入っていたらJump状態に切り替える
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<PlayerJumpState>());
	}
	//吸い込み入力が入っていたらInhale状態に切り替える
	else if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<PlayerInhaleState>());
	}

	player.UpdatePhysics();
}

void PlayerIdleState::Exit(Player& player)
{

}