#pragma once
#include "StateBase.h"

namespace PlayerState
{
	class DeadAnimState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& inpit)override;
		void Exit(Player& player)override;
	private:
		int upCount_;
	};
}
