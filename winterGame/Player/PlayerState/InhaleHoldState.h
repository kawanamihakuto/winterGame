#pragma once
#include "StateBase.h"
namespace PlayerState
{
	/// <summary>
	/// 吸い込み状態継続ステート
	/// </summary>
	class InhaleHoldState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& input) override;
		void Exit(Player& player)override;
	};
}


