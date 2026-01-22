#pragma once
#include "BossStateBase.h"

namespace BossState
{
	class NormalShotState :public BossStateBase
	{
	public:
		NormalShotState();
		virtual ~NormalShotState();
		/// <summary>
		/// その状態になった時、１回だけ呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		void Enter(BossBase& boss)override;
		/// <summary>
		/// その状態のとき毎フレーム呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		virtual void Update(BossBase& boss)override;
		/// <summary>
		/// その状態が終わる時、１回だけ呼ばれる関数
		/// </summary>
		/// <param name="player">プレイヤーの参照</param>
		virtual void Exit(BossBase& boss) override;
		/// <summary>
		/// 現在のステートを取得する関数
		/// </summary>
		/// <returns>現在のステート</returns>
		BossStateType GetState() const override { return BossStateType::NormalShot; }

	};
}



