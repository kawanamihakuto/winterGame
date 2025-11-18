#pragma once
#include "../Base/GameObject.h"
#include<memory>
class PlayerStateBase;
class Player;
class Input;
class Rect;
class Camera;
/// <summary>
/// プレイヤーの各画像
/// </summary>
struct PlayerImages
{
	int idle;
	int move;
	int jump;
	int inhale;
};
/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public GameObject
{
public:
	//現在のステートを入れる変数
	std::unique_ptr<PlayerStateBase>state_;

	Player(PlayerImages& imgs);
	~Player();

	void Init()override;
	void Update()override;
	void Update(Input& input);
	void Draw()override;
	void Draw(Camera& camera);

	//ポジションのゲッター
	 Vector2 GetPosition(){ return position_; }
	 //ポジションのセッター
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocityのゲッター
	Vector2 GetVelocity() { return velocity_; }
	//Velocityのセッター
	void SetVelocity(const Vector2& dir) { velocity_ = dir; }
	
	//Rectのゲッター
	Rect& GetHitRect() { return rect_; }
	
	//現在の画像ハンドルのゲッター
	int GetGraph() { return currentImage_; }
	//現在の画像ハンドルのセッター
	void SetGraph(int handle) { currentImage_ = handle; }

	//当たり判定用のカラーのゲッター
	int GetRectColor() { return rectColor_; }
	//当たり判定用のカラーのセッター
	void SetRectColor(int color) { rectColor_ = color; }

	//HPのゲッター
	int GetHp() { return hp_; }
	//HPのセッター
	void SetHp(int hp) { hp_ = hp; }
	
	//プレイヤーの画像すべてのゲッター
	const PlayerImages& GetImages()const { return images_; }

	//吸い込みオブジェクトを生成するかのゲッター
	bool GetGenerateInhale() { return isGenerateInhale_; }
	//吸い込みオブジェクトを生成するかのセッター
	void SetGenerateInhale(bool isGenerate) { isGenerateInhale_ = isGenerate; }

	//吸い込みオブジェクトを削除するかのゲッター
	bool GetDeleteInhale() { return isDeleteInhale_; }
	//吸い込みオブジェクトを削除するかのセッター
	void SetDeleteInhale(bool isDelete) { isDeleteInhale_ = isDelete; }

	//右を向いているかどうかのゲッター
	bool GetIsRight() { return isRight_; }
	//右を向いているかどうかのセッター
	void SetIsRight(bool isRight) { isRight_ = isRight; }

	/// <summary>
	/// ステート切り替えの関数
	/// </summary>
	/// <param name="newState">切り替えるステート</param>
	void ChangeState(std::unique_ptr<PlayerStateBase>newState);

	/// <summary>
	/// 重力用関数
	/// </summary>
	void Gravity();

	/// <summary>
	/// 移動を適用する関数
	/// </summary>
	void ApplyMovement();
	/// <summary>
	/// 物理的な移動処理のまとめ
	/// </summary>
	void UpdatePhysics();
private:
	//速度ベクトル
	Vector2 velocity_;
	//地面にいるかどうか
	bool isGround_;
	//画像ハンドルをまとめて持つ
	PlayerImages images_;
	//現在の画像
	int currentImage_;
	//プレイヤーのHP
	int hp_;
	//当たり判定用のカラー
	int rectColor_;
	//吸い込みオブジェクトを生成するリクエスト
	bool isGenerateInhale_;
	//吸い込みオブジェクトを削除するリクエスト
	bool isDeleteInhale_;
	//右を向いているかどうか
	bool isRight_;
};
/// <summary>
/// プレイヤーステートの基底クラス
/// </summary>
class PlayerStateBase
{
public:
	virtual ~PlayerStateBase() = default;
	/// <summary>
	/// その状態になった時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Enter(Player& player){};
	/// <summary>
	/// その状態のとき毎フレーム呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	/// <param name="input">入力を受け取るためのInputの参照</param>
	virtual void Update(Player& player,Input& input) = 0;
	/// <summary>
	/// その状態が終わる時、１回だけ呼ばれる関数
	/// </summary>
	/// <param name="player">プレイヤーの参照</param>
	virtual void Exit(Player& player) {};
};
/// <summary>
/// Idle状態クラス
/// </summary>
class IdleState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player,Input&input) override;
};
/// <summary>
/// Move状態クラス
/// </summary>
class MoveState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
};
/// <summary>
/// Jamp状態クラス
/// </summary>
class JumpState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
};
/// <summary>
/// ヒット状態クラス
/// </summary>
class HitState :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player,Input& inpit)override;
	void Exit(Player& player)override;
};
/// <summary>
/// 吸い込み状態クラス
/// </summary>
class InhaleState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

class MouthHoldState : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
	void Exit(Player& player)override;
};

