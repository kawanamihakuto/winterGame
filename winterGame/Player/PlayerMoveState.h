#pragma once
#include "PlayerStateBase.h"


/// <summary>
/// Moveó‘ÔƒNƒ‰ƒX
/// </summary>
class PlayerMoveState :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

