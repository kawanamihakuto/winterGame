#pragma once
#include "StateBase.h"

namespace PlayerState
{
	/// <summary>
	/// ヒットストップしている状態クラス
	/// </summary>
	class HitStopState :public StateBase
	{
	public:
		void Enter(Player& player)override;
		void Update(Player& player, Input& inpit)override;
		void Exit(Player& player)override;
	private:
		int HitStopCount_;
	};

}


