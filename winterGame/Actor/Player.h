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

	//ポジションのゲッター・セッター
	 Vector2 GetPosition(){ return position_; }
	void SetPosition(const Vector2& pos) { position_ = pos; }

	//Velocityのゲッター・セッター
	Vector2 GetVelocity() { return velocity_; }
	void SetVelocity(const Vector2& dir) { velocity_ = dir; }
	
	//Rectのゲッター・セッター
	Rect& GetHitRect() { return rect_; }
	
	//画像ハンドルのゲッター・セッター
	void SetGraph(int handle) { currentImage_ = handle; }
	int GetGraph() { return currentImage_; }

	//当たり判定用のカラーのセッター・ゲッター
	void SetRectColor(int color) { rectColor_ = color; }
	int GetRectColor() { return rectColor_; }

	//HPのゲッター・セッター
	void SetHp(int hp) { hp_ = hp; }
	int GetHp() { return hp_; }

	//imagesのゲッター
	const PlayerImages& GetImages()const { return images_; }

	//吸い込みオブジェクトを生成するかのゲッター・セッター
	bool GetGenerateInhale() { return isGenerateInhale_; }
	void SetGenerateInhale(bool isGenerate) { isGenerateInhale_ = isGenerate; }

	bool GetDeleteInhale() { return isDeleteInhale_; }
	void SetDeleteInhale(bool isDelete) { isDeleteInhale_ = isDelete; }

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
	//プレイヤーのHP;
	int hp_;
	//当たり判定用のカラー
	int rectColor_;
	//吸い込みオブジェクトを生成するリクエスト
	bool isGenerateInhale_;
	//吸い込みオブジェクトを削除するリクエスト
	bool isDeleteInhale_;
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

