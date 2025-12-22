#include<DxLib.h>
#include "Player.h"
#include"GameScene.h"
#include"Collision/Rect.h"
#include"Input.h"
#include"Camera.h"
#include"IdleState.h"
#include"MoveState.h"
#include"JumpState.h"
#include"HitState.h"
#include"InhaleState.h"
#include"Stage/Stage.h"

constexpr int kInhaledRectWidth = 8;

Player::Player(int graphHandle) :
	velocity_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(false),
	currentImage_(graphHandle),
	hp_(5),
	rectColor_(0x0000ff),
	isGenerateInhale_(false),
	isDeleteInhale_(false),
	isRight_(true),
	isInhaleHold_(false),
	mouthState_(MouthState::empty),
	graphCutNo_(PlayerGraphCutNo::mouthClosed),
	isSpit_(false),
	starOrAir_(StarOrAir::star),
	isGanarateInhaledRect_(false),
	isDeleteInhaledRect_(false),
	invincinleFrame_(0),
	nockBackTime_(0)
{
	state_ = std::make_unique<PlayerState::IdleState>();
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
}
void Player::Update(Input& input,Stage& stage)
{
	isGenerateInhale_ = false;
	isDeleteInhale_ = false;
	//現在の状態のUpdateを呼び出す
	state_->Update(*this, input);

	Rect tileRect;

	//いったんisGroundをfalseにする
	isGround_ = false;
	//重力
	Gravity();
	ApplyMovementY();
	//Rectの更新
	rect_.SetCenter(
		position_.x,
		position_.y,
		PlayerConstant::kWidth * PlayerConstant::kRectSize,
		PlayerConstant::kHeight * PlayerConstant::kRectSize
	);
	MapCollisionY(stage, tileRect);

	//X方向の移動
	ApplyMovementX();
	//Rectの更新
	rect_.SetCenter(
		position_.x,
		position_.y,
		PlayerConstant::kWidth * PlayerConstant::kRectSize,
		PlayerConstant::kHeight * PlayerConstant::kRectSize
	);
	//X方向のマップ衝突判定
	MapCollisionX(stage, tileRect);
	
	printfDx("y=%.4f vy=%.4f ground=%d\n",
		position_.y, velocity_.y, isGround_);
}

void Player::Draw()
{
}

void Player::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);
	
	int srcX = PlayerConstant::kWidth * static_cast<int>(graphCutNo_);
	int srcY = 0;

	//プレイヤー表示
	DrawRectRotaGraph(
		(int)screen.x,
		(int)screen.y-5.0f,
		srcX, srcY,
		16, 16,
		3.0,
		0.0,
		currentImage_,
		TRUE,
		!isRight_
	);
#ifdef _DEBUG
	//当たり判定表示
	Rect drawRect = rect_;
	drawRect.SetCenter(screen.x, screen.y,
		PlayerConstant::kWidth * PlayerConstant::kRectSize,
		PlayerConstant::kHeight * PlayerConstant::kRectSize);
	drawRect.Draw(rectColor_, false);

	//プレイヤーのHP表示
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
#endif // _DEBUG
}

Rect Player::GetColliderRect() const
{
	return rect_;
}

CollisionLayer Player::GetCollisionLayer() const
{
	return CollisionLayers::kNormalPlayer;
}

CollisionLayer Player::GetHitMask() const
{
	return CollisionLayers::kEnemy;
}

void Player::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		hp_ -= 1;

		if (position_.x - other.GetPosition().x <= 0)
		{
			velocity_.x = -PlayerConstant::kNockbackSpeed;
		}
		else
		{
			velocity_.x = PlayerConstant::kNockbackSpeed;
		}
		nockBackTime_ = 0;
		//プレイヤーの状態遷移
		ChangeState(std::make_unique<PlayerState::HitState>());
	}
}

bool Player::IsNockBackEnd()
{ 
	if (nockBackTime_ >= PlayerConstant::kNockBackTimeMax)
	{
		nockBackTime_ = 0;
		return true;
	}	 
	return false;
}

void Player::ChangeState(std::unique_ptr<StateBase> newState)
{
	//プレイヤーの状態を切り替える処理
	if (state_ != newState)
	{
		//現在の状態のExitを呼ぶ
		state_->Exit(*this);
		//次の状態に切り替える
		state_ = std::move(newState);
		//切り替えた後の現在の状態のEnterを呼ぶ
		state_->Enter(*this);
	}
}

void Player::Gravity()
{
	if (!isGround_)
	{
		//重力分下方向に力を加える
		velocity_.y += PlayerConstant::kGravity;
	}
}

void Player::ApplyMovementX()
{
	//摩擦処理
	velocity_.x *= PlayerConstant::kFriction;
	position_.x += velocity_.x;
}

void Player::ApplyMovementY()
{
	position_.y += velocity_.y;
}

void Player::MapCollisionX(const Stage& stage,Rect tileRect)
{
	if (stage.IsCollision(rect_, tileRect))
	{
		// 右に移動して壁に当たった場合
		if (velocity_.x > 0.0f)
		{
			// プレイヤーの右端をタイルの左端に合わせる
			position_.x = tileRect.left_ - rect_.GetWidth() * 0.5f - 0.01f;
		}
		// 左に移動して壁に当たった場合
		else if (velocity_.x < 0.0f)
		{
			// プレイヤーの左端をタイルの右端に合わせる
			position_.x = tileRect.right_ + rect_.GetWidth() * 0.5f+0.01f;
		}

		// 壁に当たったのでX速度はゼロ
		velocity_.x = 0.0f;

		// 押し戻した後は必ずRectを更新
		rect_.SetCenter(
			position_.x,
			position_.y,
			PlayerConstant::kWidth * PlayerConstant::kRectSize,
			PlayerConstant::kHeight * PlayerConstant::kRectSize
		);
	}
}

void Player::MapCollisionY(const Stage& stage,Rect tileRect)
{	
	if (stage.IsCollision(rect_, tileRect))
	{
		// 落下中（床）
		if (velocity_.y > 0.0f)
		{
			// プレイヤーの足を床の上にぴったり合わせる
			position_.y = tileRect.top_ - rect_.GetHeight() * 0.5f - 0.01f;

			// 落下速度を完全に止める
			velocity_.y = 0.0f;

			// 接地フラグをtrueにする
			isGround_ = true;
		}
		// 上昇中（天井）
		else if (velocity_.y < 0.0f)
		{
			// プレイヤーの頭を天井の下に合わせる
			position_.y = tileRect.bottom_ + rect_.GetHeight() * 0.5f+0.01f;

			// 上方向速度を止める
			velocity_.y = 0.0f;
		}
		// 押し戻し後のRect更新
		rect_.SetCenter(
			position_.x,
			position_.y,
			PlayerConstant::kWidth * PlayerConstant::kRectSize,
			PlayerConstant::kHeight * PlayerConstant::kRectSize
		);
	}
}
