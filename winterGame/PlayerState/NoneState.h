#pragma once
#include "StateBase.h"

namespace PlayerState
{
	//‘€ì‚ğó‚¯•t‚¯‚È‚¢ó‘Ô
	class NoneState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::None; }
	};
}