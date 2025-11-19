#pragma once
#include "StateBase.h"

namespace PlayerState
{
	/// <summary>
	/// Œû‚ÉŠÜ‚ñ‚Å‚¢‚éó‘ÔƒNƒ‰ƒX
	/// </summary>
	class MouthHoldState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;
	};

}

