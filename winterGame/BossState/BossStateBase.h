#pragma once

enum class BossStateType
{
	Idle,
	Attack
};

class BossBase;
class BossStateBase
{
public:
	virtual ~BossStateBase() = default;
	/// <summary>
	/// その状態になった時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Enter(BossBase& boss) = 0;
	/// <summary>
	/// その状態のとき毎フレーム呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Update(BossBase& boss) = 0;
	/// <summary>
	/// その状態が終わる時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Exit(BossBase& boss) = 0;
	/// <summary>
	/// 現在のステートを取得する関数
	/// </summary>
	/// <returns>現在のステート</returns>
	virtual BossStateType GetState() const = 0;
};

