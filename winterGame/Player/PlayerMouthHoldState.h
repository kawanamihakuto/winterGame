#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// Œû‚ÉŠÜ‚ñ‚Å‚¢‚éó‘ÔƒNƒ‰ƒX
/// </summary>
class PlayerMouthHoldState :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

