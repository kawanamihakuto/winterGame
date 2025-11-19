#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// Idleó‘ÔƒNƒ‰ƒX
/// </summary>
class PlayerIdleState :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

