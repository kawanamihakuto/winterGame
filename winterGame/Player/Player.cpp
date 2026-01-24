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
#include"Application.h"
#include"HitStopState.h"
#include"DeadAnimState.h"
#include"Item.h"
#include"BossBattleState.h"
namespace
{
	constexpr int kInhaledRectWidth = 8;
	constexpr int kInvincibleTime = 45;
	constexpr int kInvincibleFlashingInterval = 4;
	constexpr int kDefaultHp = 3;
	constexpr Vector2 kStage1StartPosition = { 640,751 };
	constexpr Vector2 kStage2StartPosition = { 640,607.7 };
	constexpr Vector2 kStage3StartPosition = { 640,751 };

	//ステージ1用定数
	constexpr int kCeiling = 305;
	constexpr int kLeftLimit = 16;
	constexpr int kRightLimit = 7171;

	constexpr int kCeiling2 = 272;
	constexpr int kRightLimit2 = 1262;

}


Player::Player(int graphHandle) :
	velocity_{ 0.0f,0.0f },
	GameObject(kStage1StartPosition),
	isGround_(false),
	currentImage_(graphHandle),
	hp_(kDefaultHp),
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
	invincibleFrame_(0),
	isInvincible_(false),
	nockBackTime_(0),
	isCollisionDoor_(false),
	isDead_(false),
	deadAnimAngleNum_(0.0),
	stageNo_(1),
	size_(3.0),
	isStartBossBattle_(false),
	requestCameraShake_(false),
	isPlayMovie_(false)
{
	state_ = std::make_unique<PlayerState::IdleState>();
}

Player::~Player()
{
}

void Player::Init()
{

}

void Player::Init(int stageNo)
{
	stageNo_ = stageNo;
	if (stageNo_ == 1)
	{
		position_ = kStage1StartPosition;
	}
	else if (stageNo_ == 2)
	{
		position_ = kStage2StartPosition;
	}
	else if (stageNo_ == 3)
	{
		position_ = kStage3StartPosition;
	}

	state_ = std::make_unique<PlayerState::IdleState>();
	mouthState_ = MouthState::empty;
	graphCutNo_ = PlayerGraphCutNo::mouthClosed;
	velocity_ = { 0.0f,0.0f };
	isRight_ = true;
}

void Player::Update()
{
}
void Player::Update(Input& input, Stage& stage,Camera& camera)
{
	isCollisionDoor_ = false;
	isGenerateInhale_ = false;
	isDeleteInhale_ = false;
	if (hp_ <= 0)
	{
		isDead_ = true;
	}
	//現在の状態のUpdateを呼び出す
	state_->Update(*this, input);

	if (!isDead_)
	{
		if (state_->GetState() == PlayerStateType::BossBattle)
		{
			Rect tileRect;

			//いったんisGroundをfalseにする
			isGround_ = false;
			ApplyMovementY();
			//Rectの更新
			rect_.SetCenter(
				position_.x,
				position_.y,
				PlayerConstant::kWidth * (size_ - 2.0),
				PlayerConstant::kHeight * (size_ - 2.2)
			);
			MapCollisionY(stage, tileRect);

			//X方向の移動
			ApplyMovementX();
			//Rectの更新
			rect_.SetCenter(
				position_.x,
				position_.y,
				PlayerConstant::kWidth * (size_ - 2.0),
				PlayerConstant::kHeight * (size_ - 2.2)
			);
			//X方向のマップ衝突判定
			MapCollisionX(stage, tileRect);

		}
		else
		{
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

		}
	}

	//-------------------
	//ステージ1用の設定
	//-------------------
	switch (stageNo_)
	{
	case 1:
		if (isDead_)
		{
			ApplyMovementX();
			ApplyMovementY();
		}
		else
		{
			//落下死
			if (position_.y >= 1100)
			{
				isDead_ = true;
				ChangeState(std::make_unique<PlayerState::DeadAnimState>());
			}
			//天井
			if (position_.y <= kCeiling)
			{
				position_.y = kCeiling;
			}
			//ステージの左端
			if (position_.x <= kLeftLimit)
			{
				position_.x = kLeftLimit;
			}
			//ステージの右端
			if (position_.x >= kRightLimit)
			{
				position_.x = kRightLimit;
			}
		}
		
		break;
	case 2:
		if (isDead_)
		{
			ApplyMovementX();
			ApplyMovementY();
		}
		else
		{
			//天井
			if (position_.y <= kCeiling2)
			{
				position_.y = kCeiling2;
			}
			//ステージの左端
			if (position_.x <= kLeftLimit)
			{
				position_.x = kLeftLimit;
			}
			//ステージの右端
			if (position_.x >= kRightLimit2)
			{
				position_.x = kRightLimit2;
			}
		}
		
		break;
	case 3:
		if (isDead_)
		{
			ApplyMovementX();
			ApplyMovementY();
		}
		else
		{
			//天井
			if (position_.y <= kCeiling)
			{
				position_.y = kCeiling;
			}
			//ステージの左端
			if (position_.x <= kLeftLimit)
			{
				position_.x = kLeftLimit;
			}
			auto wsize = Application::GetInstance().GetWindowSize();
			if (position_.x <= camera.GetPosition().x - (wsize.w / 2))
			{
				position_.x = camera.GetPosition().x - (wsize.w / 2);
			}
			if (position_.x >= camera.GetPosition().x + (wsize.w / 2))
			{
				position_.x = camera.GetPosition().x + (wsize.w / 2);
			}
			if (position_.y <= camera.GetPosition().y - (wsize.h / 2))
			{
				position_.y = camera.GetPosition().y - (wsize.h / 2);
			}
			if (position_.y >= camera.GetPosition().y + (wsize.h * 0.4f))
			{
				position_.y = camera.GetPosition().y + (wsize.h * 0.4f);
			}
		}
		break;
	}

#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_G))
	{
		if (stageNo_ == 1)
		{
			position_.x = kRightLimit;
		}
		else if (stageNo_ == 2)
		{
			position_.y = 2290;
		}
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		hp_ = 0;
		isDead_ = true;
		ChangeState(std::make_unique<PlayerState::DeadAnimState>());
	}
#endif // _DEBUG
}

void Player::Draw()
{
}

void Player::Draw(Camera& camera)
{
	Vector2 screen = camera.WorldToScreen(position_);

	int srcX = PlayerConstant::kWidth * static_cast<int>(graphCutNo_);
	int srcY = 0;

	if (isDead_)
	{
		DrawRectRotaGraph(
			(int)screen.x,
			(int)screen.y - 5.0f,
			srcX, srcY,
			16, 16,
			size_,
			deadAnimAngleNum_,
			currentImage_,
			TRUE,
			!isRight_
		);
	}
	else
	{
		if (isInvincible_)
		{
			if ((invincibleFrame_++ / kInvincibleFlashingInterval) % 2 == 0)
			{
				//プレイヤー表示
				DrawRectRotaGraph(
					(int)screen.x,
					(int)screen.y - 5.0f,
					srcX, srcY,
					16, 16,
					size_,
					0.0,
					currentImage_,
					TRUE,
					!isRight_
				);
			}
			if (invincibleFrame_ >= kInvincibleTime)
			{
				invincibleFrame_ = 0;
				isInvincible_ = false;
			}
		}
		else
		{
			//プレイヤー表示
			DrawRectRotaGraph(
				(int)screen.x,
				(int)screen.y - 5.0f,
				srcX, srcY,
				16, 16,
				size_,
				0.0,
				currentImage_,
				TRUE,
				!isRight_
			);
		}
	}

#ifdef _DEBUG
	//当たり判定表示
	Rect drawRect = rect_;
	if (state_->GetState() == PlayerStateType::BossBattle)
	{
		drawRect.SetCenter(screen.x, screen.y,
			PlayerConstant::kWidth * (size_ - 2.0),
			PlayerConstant::kHeight * (size_ - 2.2));
	}
	else
	{
		drawRect.SetCenter(screen.x, screen.y,
			PlayerConstant::kWidth * PlayerConstant::kRectSize,
			PlayerConstant::kHeight * PlayerConstant::kRectSize);
	}
	drawRect.Draw(rectColor_, false);

	//プレイヤーのHP表示
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
	DrawFormatString(16, 16, 0xffffff, "%f , %f", position_.x, position_.y);
	DrawFormatString(16, 32, 0xffffff, "%d", isInvincible_);
	DrawFormatString(16, 48, 0xffffff, "%f , %f", velocity_.x, position_.y);
	DrawFormatString(16, 120, 0xffffff, "%f", size_);
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
	return CollisionLayers::kEnemy |
		CollisionLayers::kDoor |
		CollisionLayers::kItem|
		CollisionLayers::kBossAttack|
		CollisionLayers::kBoss;
}

void Player::OnCollision(GameObject& other)
{
	if (other.GetCollisionLayer() & CollisionLayers::kEnemy)
	{
		if (isInvincible_)
		{
			return;
		}
		hp_ -= 1;
		isInvincible_ = true;
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

	if (other.GetCollisionLayer() & CollisionLayers::kBoss)
	{
		if (isInvincible_)
		{
			return;
		}
		hp_ -= 1;
		isInvincible_ = true;
	}

	if (other.GetCollisionLayer() & CollisionLayers::kBossAttack)
	{
		if (isInvincible_)
		{
			return;
		}
		hp_ -= 1;
		isInvincible_ = true;
	}

	if (other.GetCollisionLayer() & CollisionLayers::kDoor)
	{
		isCollisionDoor_ = true;
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

int Player::GetMaxHp()
{
	return kDefaultHp;
}

void Player::OnGetItem(ItemType itemType)
{
	if (itemType == ItemType::dragonFruit)
	{
		ChangeState(std::make_unique<PlayerState::BossBattleState>());
		isStartBossBattle_ = true;
	}
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
		if (state_->GetState() == PlayerStateType::BossBattle)
		{

		}
		else
		{
			//重力分下方向に力を加える
			velocity_.y += PlayerConstant::kGravity;
		}
	}
}

void Player::ApplyMovementX()
{
	if (isGround_)
	{
		//摩擦処理
		velocity_.x *= PlayerConstant::kFriction;
	}
	else
	{
		//空中にいるときの慣性を調整
		velocity_.x *= 0.95f;
	}
	position_.x += velocity_.x;
}

void Player::ApplyMovementY()
{
	position_.y += velocity_.y;
}

void Player::MapCollisionX(const Stage& stage, Rect tileRect)
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
			position_.x = tileRect.right_ + rect_.GetWidth() * 0.5f + 0.01f;
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

void Player::MapCollisionY(const Stage& stage, Rect tileRect)
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
			position_.y = tileRect.bottom_ + rect_.GetHeight() * 0.5f + 0.01f;

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
