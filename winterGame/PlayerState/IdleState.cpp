#include "IdleState.h"
#include"Player.h"
#include"Input.h"
#include"MoveState.h"
#include"InhaleState.h"
#include"JumpState.h"
#include"SpitState.h"
#include"HoveringState.h"
#include"SwallowState.h"
void PlayerState::IdleState::Enter(Player& player)
{
	switch (player.GetMouthState())
	{
	case MouthState::empty:
		//Œû‚ğ•Â‚¶‚é
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthClosed);
		break;
	case MouthState::holdingEnemy:
		//‚Ù‚¨‚Î‚è
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
		break;
	case MouthState::holdingAir:
		player.SetPlayerGraphCutNo(PlayerGraphCutNo::mouthFull);
		break;
	}
}

void PlayerState::IdleState::Update(Player& player, Input& input)
{
	switch (player.GetMouthState())
	{
	case MouthState::empty:

		if (player.GetIsGround())
		{
			//‹z‚¢‚İ“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çInhaleó‘Ô‚ÉØ‚è‘Ö‚¦‚é
			if (input.IsTriggered("attack"))
			{
				player.ChangeState(std::make_unique<InhaleState>());
				return;
			}
		}
		else
		{
			//‹z‚¢‚İ“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çInhaleó‘Ô‚ÉØ‚è‘Ö‚¦‚é
			if (input.IsPressed("attack"))
			{
				player.ChangeState(std::make_unique<InhaleState>());
				return;
			}
		}
		
		if (input.IsPressed("up"))
		{
			player.ChangeState(std::make_unique<HoveringState>());
			return;
		}
		break;
	case MouthState::holdingEnemy:
		if (input.IsTriggered("attack"))
		{
			player.ChangeState(std::make_unique<SpitState>());
			return;
		}
		break;
	}

	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//¶‚Ì“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çMoveó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<MoveState>());
		return;
	}
	//‰E‚Ì“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çMoveó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
		return;
	}
	//ƒWƒƒƒ“ƒv“ü—Í‚ª“ü‚Á‚Ä‚¢‚½‚çJumpó‘Ô‚ÉØ‚è‘Ö‚¦‚é
	else if (input.IsPressed("jump") && player.GetIsGround())
	{
		player.ChangeState(std::make_unique<JumpState>());
		return;
	}
	else if ((input.IsTriggered("down") && player.GetMouthState() == MouthState::holdingEnemy))
	{
		player.ChangeState(std::make_unique<SwallowState>());
		return;
	}
}

void PlayerState::IdleState::Exit(Player& player)
{

}