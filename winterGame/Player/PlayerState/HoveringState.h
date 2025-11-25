#pragma once
#include "StateBase.h"

namespace PlayerState
{
	/// <summary>
	/// ホバリング状態クラス
	/// </summary>
	class HoveringState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;
	};
}