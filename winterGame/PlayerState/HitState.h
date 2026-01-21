#pragma once
#include "StateBase.h"

namespace PlayerState
{
	/// <summary>
	/// ヒット状態クラス
	/// </summary>
	class HitState : public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& inpit)override;
		void Exit(Player& player)override;

		PlayerStateType GetState() const override { return PlayerStateType::Hit; }
	};
}


