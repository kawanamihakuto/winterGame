#pragma once
#include "../Base/GameObject.h"
#include<memory>
class StateBase;
class Player;
class Input;
class Rect;
class Camera;

//プレイヤー関連の定数群
namespace PlayerConstant
{
	//プレイヤーの幅
	constexpr int kWidth = 32;
	//プレイヤーの高さ
	constexpr int kHeight = 32;
	//プレイヤーの拡大倍率
	constexpr float kSize = 2.0f;
	//仮の地面
	constexpr int kGround = 400;
	//横方向の移動スピード
	constexpr float kMoveSpeed = 1.0f;
	//重力
	constexpr float kGravity = 0.4f;
	//ジャンプの強さ
	constexpr float kJumpPower = 8.0f;
	//横方向のマックススピード
	constexpr float kMaxSpeed = 3.0f;
	//摩擦の強さ
	constexpr float kFriction = 0.90f;
}

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
	std::unique_ptr<StateBase>state_;

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
	void ChangeState(std::unique_ptr<StateBase>newState);

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