#pragma once
#include "StateBase.h"
namespace PlayerState
{
	/// <summary>
	/// BossBattleó‘ÔƒNƒ‰ƒX
	/// </summary>
	class BossBattleState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::BossBattle; }
	private:
		int AttackDelay = 0;
		double sizeCount_ = 3.0;
	};
}

