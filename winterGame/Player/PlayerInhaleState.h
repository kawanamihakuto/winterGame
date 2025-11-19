#pragma once
#include"PlayerStateBase.h"

/// <summary>
/// ‹z‚¢‚İó‘ÔƒNƒ‰ƒX
/// </summary>
class PlayerInhaleState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

