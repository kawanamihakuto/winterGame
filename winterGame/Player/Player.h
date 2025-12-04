#pragma once
#include "Base/GameObject.h"
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
	constexpr int kWidth = 16;
	//プレイヤーの高さ
	constexpr int kHeight = 16;
	//プレイヤーの拡大倍率
	constexpr float kSize = 3.0f;
	//プレイヤーの当たり判定拡大倍率
	constexpr float kRectSize = 1.0f;
	//仮の地面
	constexpr int kGround = 720;
	//横方向の移動スピード
	constexpr float kMoveSpeed = 1.0f;
	//重力
	constexpr float kGravity = 0.3f;
	//ジャンプの強さ
	constexpr float kJumpPower = 8.0f;
	//横方向のマックススピード
	constexpr float kMaxSpeed = 3.0f;
	//摩擦の強さ
	constexpr float kFriction = 0.90f;
	//ホバリングの強さ
	constexpr float kHoveringPower = 4.0f;

	constexpr float kNockbackSpeed = 4.0f;
	constexpr int kNockBackTimeMax = 10;
}

/// <summary>
/// プレイヤーがほおばっているかどうか
/// </summary>
enum class MouthState
{
	empty,
	holdingEnemy,
	holdingAir
};
/// <summary>
/// プレイヤーの画像の切り取りラインをenumで決める
/// </summary>
enum class PlayerGraphCutNo
{
	mouthClosed,
	mouthOpen,
	mouthFull
};

enum class StarOrAir
{
	star,
	air
};
/// <summary>
/// プレイヤークラス
/// </summary>
class Player :public GameObject
{
public:
	Player(int GraphHandle);
	~Player();

	void Init()override;
	void Update()override;
	void Update(Input& input);
	void Draw()override;
	void Draw(Camera& camera);

	//当たり判定の形を返すゲッター
	Rect GetColliderRect()const override;
	//自身のレイヤーを返すゲッター
	CollisionLayer GetCollisionLayer()const override;
	//当たりたいレイヤーを返すゲッター
	CollisionLayer GetHitMask()const override;
	//当たった時の処理を行う関数
	void OnCollision(GameObject& other) override;

	//ポジションのゲッター
	Vector2 GetPosition() { return position_; }
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

	//吸い込みオブジェクトを生成するかのゲッター
	bool GetGenerateInhale() { return isGenerateInhale_; }
	//吸い込み状態になったときに呼ぶ
	void StartInhale() { isGenerateInhale_ = true; }

	//吸い込みオブジェクトを削除するかのゲッター
	bool GetDeleteInhale() { return isDeleteInhale_; }
	//吸い込み状態が終わるときに呼ぶ
	void EndInhale() { isDeleteInhale_ = true; }

	//右を向いているかどうかのゲッター
	bool GetIsRight() { return isRight_; }
	//右を向いているかどうかのセッター
	void SetIsRight(bool isRight) { isRight_ = isRight; }

	//吸い込み状態を継続するかどうかのゲッター
	bool GetIsInhaledHold() { return isInhaleHold_; }
	//吸い込み状態を継続するかどうかのセッター
	void SetIsInhaledHold(bool isInhaledHold) { isInhaleHold_ = isInhaledHold; }

	//ほおばっているかどうかのゲッター
	MouthState GetMouthState() { return mouthState_; }
	//ほおばっているかどうかのセッター
	void SetMouthState(MouthState mouthState) { mouthState_ = mouthState; }
	//プレイヤーの画像の切り取り位置のセッター
	void SetPlayerGraphCutNo(PlayerGraphCutNo pgcn) { graphCutNo_ = pgcn; }

	//吐き出しフラグのゲッター
	bool GetIsSpit() { return isSpit_; }
	//吐き出しフラグのセッター
	void SetIsSpit(bool isSpit) { isSpit_ = isSpit; }

	StarOrAir GetStarOrAir() { return starOrAir_; }
	void SetStarOrAir(StarOrAir starOrAir) { starOrAir_ = starOrAir; }

	bool GetIsGround()const { return isGround_; }

	void OnJump() { isGround_ = false; }
	//ノックバックする時間のカウンター
	void NockBackTimeUpdate() { nockBackTime_++; }
	//ノックバック状態が終わったかどうかのゲッター
	bool IsNockBackEnd();

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
	//現在のステートを入れる変数
	std::unique_ptr<StateBase>state_;
	//速度ベクトル
	Vector2 velocity_;
	//地面にいるかどうか
	bool isGround_;
	//現在の画像
	int currentImage_;
	//プレイヤーのHP
	int hp_;
	//当たり判定用のカラー
	int rectColor_;
	//吸い込みオブジェクトを生成するリクエストフラグ
	bool isGenerateInhale_;
	//吸い込みオブジェクトを削除するリクエストフラグ
	bool isDeleteInhale_;
	//右を向いているかどうか
	bool isRight_;
	//吸い込み状態を継続するかどうか
	bool isInhaleHold_;
	//ほおばっているかどうかのステート
	MouthState mouthState_;
	//プレイヤーの画像切り取りラインを入れる変数
	PlayerGraphCutNo graphCutNo_;
	//吐き出しのリクエストフラグ
	bool isSpit_;
	//星弾か空気弾か決めるための変数
	StarOrAir starOrAir_;
	//吸い込み状態中に出す当たり判定の生成リクエスト
	bool isGanarateInhaledRect_;
	//吸い込み状態中に出す当たり判定の削除リクエスト
	bool isDeleteInhaledRect_;
	//ノックバックの時間カウンター
	int nockBackTime_;
	//無敵時間用フレームカウンター
	int invincinleFrame_;
};