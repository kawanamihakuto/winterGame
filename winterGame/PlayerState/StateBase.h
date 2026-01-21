#pragma once


enum class PlayerStateType
{
	Idle,
	Move,
	Jump,
	BossBattle,
	Swallow,
	Spit,
	None,
	Inhale,
	InhaleHold,
	Hovering,
	Hit,
	HitStop,
	DeadAnim
};

class Player;
class Input;
/// <summary>
/// プレイヤーステートの基底クラス
/// </summary>
class StateBase
{
public:
	virtual ~StateBase() = default;
	/// <summary>
	/// その状態になった時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Enter(Player& player) = 0;
	/// <summary>
	/// その状態のとき毎フレーム呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	/// <param name="input">入力を受け取るためのInputの参照</param>
	virtual void Update(Player& player, Input& input) = 0;
	/// <summary>
	/// その状態が終わる時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Exit(Player& player) = 0;
	/// <summary>
	/// 現在のステートを取得する関数
	/// </summary>
	/// <returns>現在のステート</returns>
	virtual PlayerStateType GetState() const = 0;
};

