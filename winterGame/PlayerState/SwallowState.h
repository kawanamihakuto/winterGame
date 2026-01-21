#pragma once
#include "StateBase.h"
namespace PlayerState
{
	//ˆù‚İ‚İó‘ÔƒNƒ‰ƒX
	class SwallowState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::Swallow; }
	};
}


