#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// Jampó‘ÔƒNƒ‰ƒX
/// </summary>
class PlayerJumpState :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

