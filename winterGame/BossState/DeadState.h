#pragma once
#include "BossStateBase.h"
namespace BossState
{
	class DeadState : public BossStateBase
	{
	public:
		DeadState();
		virtual ~DeadState();
		/// <summary>
		/// その状態になった時、１回だけ呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		void Enter(BossBase& boss)override;
		/// <summary>
		/// その状態のとき毎フレーム呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		void Update(BossBase& boss)override;
		/// <summary>
		/// その状態が終わる時、１回だけ呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		void Exit(BossBase& boss) override;
		/// <summary>
		/// 現在のステートを取得する関数
		/// </summary>
		/// <returns>現在のステート</returns>
		BossStateType GetState() const override { return BossStateType::Dead; }
	private:
		int shakeTime_;
	};
}
