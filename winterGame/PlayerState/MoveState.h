#pragma once
#include "StateBase.h"

namespace PlayerState
{
	/// <summary>
	/// Moveó‘ÔƒNƒ‰ƒX
	/// </summary>
	class MoveState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;
	};
}


