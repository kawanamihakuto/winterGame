#pragma once
#include "StateBase.h"
namespace PlayerState
{
	/// <summary>
	/// “f‚«o‚µó‘ÔƒNƒ‰ƒX
	/// </summary>
	class SpitState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::Spit; }
	private:
		int count_;
	};
}



