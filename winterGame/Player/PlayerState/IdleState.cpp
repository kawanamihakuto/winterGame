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
		//Œû‚ğ•Â‚¶‚é
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthClosed);
		break;
	case MouthState::Holding:
		//‚Ù‚¨‚Î‚è
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
		break;
	}
	
	// velocity‚ğ0‚É‚·‚é
	player.SetVelocity({ 0.0f,0.0f });
}

void PlayerState::IdleState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//¶‚Ì“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çMoveó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//‰E‚Ì“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çMoveó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//ƒWƒƒƒ“ƒv“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çJumpó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
	}
	//‹z‚¢‚İ“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çInhaleó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsTriggered("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

	player.UpdatePhysics();
}

void PlayerState::IdleState::Exit(Player& player)
{

}