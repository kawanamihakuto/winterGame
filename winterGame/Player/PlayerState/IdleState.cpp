#include "IdleState.h"
#include"../Player.h"
#include"../../System/Input.h"
#include"MoveState.h"
#include"InhaleState.h"
#include"JumpState.h"
void PlayerState::IdleState::Enter(Player& player)
{
	switch (player.GetMouthState())
	{
	case MouthState::Empty:
		//画像をIdleに変更 
		player.SetGraph(player.GetImages().idle);
		break;
	case MouthState::Holding:
		player.SetGraph(player.GetImages().mouthHoldIdle);
		break;
	}
	
	// velocityを0にする
	player.SetVelocity({ 0.0f,0.0f });
}

void PlayerState::IdleState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//左の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//右の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//ジャンプ入力が入っていたらJump状態に切り替える
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
	}
	//吸い込み入力が入っていたらInhale状態に切り替える
	else if (input.IsTriggered("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

	player.UpdatePhysics();
}

void PlayerState::IdleState::Exit(Player& player)
{

}