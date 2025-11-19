#pragma once
#include "PlayerStateBase.h"

/// <summary>
/// ヒット状態クラス
/// </summary>
class PlayerHitState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& inpit)override;
	void Exit(Player& player)override;
};

