#pragma once
#include "StateBase.h"
namespace PlayerState
{
	/// <summary>
	/// Idleó‘ÔƒNƒ‰ƒX
	/// </summary>
	class IdleState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::Idle; }
	};
}



