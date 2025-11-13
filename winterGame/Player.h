#pragma once
#include "GameObject.h"
#include<memory>
class PlayerStateBase;
class Player;
class Input;
class Rect;
/// <summary>
/// プレイヤーの各画像
/// </summary>
struct PlayerImages
{
	int idle;
	int move;
	int jump;
};
/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public GameObject
{
public:
	//フレンドにする
	friend PlayerStateBase;

	//現在のステートを入れる変数
	std::unique_ptr<PlayerStateBase>state_;

	Player(PlayerImages& imgs);
	~Player();

	void Init()override;
	void Update()override;
	void Update(Input& input);
	void Draw()override;

	//ポジションのゲッター・セッター
	 Vector2& GetPosition(){ return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocityのゲッター・セッター
	Vector2& GetVelocity() { return velocity_; }
	void SetVelocity(const Vector2& dir) { velocity_ = dir; }
	
	//Rectのゲッター・セッター
	Rect& GetHitRect() { return rect_; }
	void SetHitRect(const Rect& rect) { rect_ = rect; }

	//<画像ハンドルのセッター>
	void SetGraph(int handle) { currentImage_ = handle; }
	int& GetGraph() { return currentImage_; }

	//imagesのゲッター
	const PlayerImages& GetImages()const { return images_; }

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

private:
	//速度ベクトル
	Vector2 velocity_;
	//地面にいるかどうか
	bool isGround_;
	//画像ハンドルをまとめて持つ
	PlayerImages images_;
	//現在の画像
	int currentImage_;
	//プレイヤーのHP;
	int hp_;
};
/// <summary>
/// プレイヤーステートの基底クラス
/// </summary>
class PlayerStateBase
{
public:
	virtual ~PlayerStateBase() = default;
	virtual void Enter(Player& player){};
	virtual void Update(Player& player,Input& input) = 0;
	virtual void Exit(Player& player) {};
};
/// <summary>
/// Idle状態クラス
/// </summary>
class Idle : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player,Input&input) override;
};
/// <summary>
/// Move状態クラス
/// </summary>
class Move : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
};
/// <summary>
/// Jamp状態クラス
/// </summary>
class Jump : public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player, Input& input) override;
};

class Hit :public PlayerStateBase
{
public:
	void Enter(Player& player)override;
	void Update(Player& player,Input& inpit)override;
	void Exit(Player& player)override;
};

