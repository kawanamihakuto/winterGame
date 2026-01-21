#pragma once
#include"StateBase.h"
namespace PlayerState
{
	/// <summary>
	/// ‹z‚¢‚İó‘ÔƒNƒ‰ƒX
	/// </summary>
	class InhaleState : public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::Inhale; }
	};
}


