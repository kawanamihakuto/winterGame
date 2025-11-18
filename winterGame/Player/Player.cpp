#include<DxLib.h>
#include "Player.h"
#include"../Scene/GameScene.h"
#include"../System/Rect.h"
#include"../System/Input.h"
#include"../System/Camera.h"
namespace
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



Player::Player(PlayerImages& imgs) :
	velocity_{ 0.0f,0.0f },
	GameObject({ 320,240 }),
	isGround_(true),
	images_(imgs),
	currentImage_(imgs.idle),
	hp_(5),
	rectColor_(0x0000ff),
	isGenerateInhale_(false),
	isDeleteInhale_(false),
	isRight_(true)
{
	state_ = std::make_unique<IdleState>();
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
void Player::Update(Input& input)
{
	//現在の状態のUpdateを呼び出す
	state_->Update(*this, input);
}

void Player::Draw()
{
	
}

void Player::Draw(Camera& camera)
{
	//プレイヤー表示
	DrawRectRotaGraph(position_.x + camera.GetDrawOffset().x, position_.y + camera.GetDrawOffset().y,
		0, 0, kWidth, kHeight,
		kSize, 0, currentImage_, true);
#ifdef _DEBUG
	//当たり判定表示
	rect_.SetCenter(position_.x + camera.GetDrawOffset().x, position_.y + (kHeight / 2) + camera.GetDrawOffset().y, kWidth, kHeight);
	rect_.Draw(rectColor_, false);
	//プレイヤーのHP表示
	DrawFormatString(0, 0, 0xffffff, "%d", hp_);
#endif // _DEBUG
}

void Player::ChangeState(std::unique_ptr<PlayerStateBase> newState)
{
	//プレイヤーの状態を切り替える処理
	if (state_)
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
	//重力分下方向に力を加える
	velocity_.y += kGravity;
}

void Player::ApplyMovement()
{
	//velをposに反映
	position_ += velocity_;

	//仮の地面判定の処理
	if (position_.y >= kGround)
	{
		position_.y = kGround;
		velocity_.y = 0.0f;
		isGround_ = true;
	}
}

void Player::UpdatePhysics()
{
	//重力処理
	Gravity();
	//velocityをpositionに加える
	ApplyMovement();
}

void IdleState::Enter(Player& player)
{
	//画像をIdleに変更 
	player.SetGraph(player.GetImages().idle);
	// velocityを0にする
	player.SetVelocity({0.0f,0.0f});
}

void IdleState::Update(Player& player, Input& input)
{
	if (input.IsPressed("left") && input.IsPressed("right"))
	{

	}
	//左の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("left"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//右の入力が入っていたらMove状態に切り替える
	else if (input.IsPressed("right"))
	{
		player.ChangeState(std::make_unique<MoveState>());
	}
	//ジャンプ入力が入っていたらJump状態に切り替える
	else if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
	}
	//吸い込み入力が入っていたらInhale状態に切り替える
	else if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}
	
	player.UpdatePhysics();
}


void MoveState::Enter(Player& player)
{
	//画像をMoveに変更
	player.SetGraph(player.GetImages().move);
}

void MoveState::Update(Player& player, Input& input)
{
	Vector2 vel = player.GetVelocity();
	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		vel.x -= kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		vel.x += kMoveSpeed;
	}
	//ジャンプ入力があったらJump状態に切り替える
	if (input.IsPressed("jump"))
	{
		player.ChangeState(std::make_unique<JumpState>());
		return;
	}
	//吸い込み入力があったらInhale状態に切り替える
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

	//摩擦処理
	vel.x *= kFriction;

	//速度制限
	if (vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	player.SetVelocity(vel);

	//速度がほぼ0になったらIdle状態に切り替える
	if (vel.x <= 0.1f&&vel.x >= -0.1)
	{
		player.ChangeState(std::make_unique<IdleState>());
	}

	player.UpdatePhysics();
}


void JumpState::Enter(Player& player)
{
	//画像をJumpに変更
	player.SetGraph(player.GetImages().jump);
	// 上方向へ速度を与える
	Vector2 vel = player.GetVelocity();
	vel.y = -kJumpPower;
	player.SetVelocity(vel);
}

void JumpState::Update(Player& player, Input& input)
{
	Vector2 vel = player.GetVelocity();

	//左右の入力で速度を変更
	if (input.IsPressed("left"))
	{
		player.SetIsRight(false);
		vel.x -= kMoveSpeed;
	}
	if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		vel.x += kMoveSpeed;
	}

	//速度制限
	if (vel.x >= kMaxSpeed)
	{
		vel.x = kMaxSpeed;
	}
	if (vel.x <= -kMaxSpeed)
	{
		vel.x = -kMaxSpeed;
	}

	player.SetVelocity(vel);
	player.UpdatePhysics();
	
	auto pos = player.GetPosition();
	//地面に着地したらIdleかMoveへ遷移
	if (pos.y >= kGround)
	{
		if (input.IsPressed("left") || input.IsPressed("right"))
		{
			player.ChangeState(std::make_unique<MoveState>());
		}
		else
		{
			player.ChangeState(std::make_unique<IdleState>());
		}
	}
	if (input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<InhaleState>());
	}

}

void HitState::Enter(Player& player)
{
	//hpを減らす処理
	int hp = player.GetHp();
	hp-=1;
	player.SetHp(hp);
#ifdef _DEBUG
	int rectColor = 0xff0000;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}
void HitState::Update(Player& player,Input& input)
{
	if (input.IsPressed("left") )
	{
		player.SetIsRight(false);
		player.ChangeState(std::make_unique<MoveState>());
	}
	else if (input.IsPressed("right"))
	{
		player.SetIsRight(true);
		player.ChangeState(std::make_unique<MoveState>());
	}
	else
	{
		player.ChangeState(std::make_unique<IdleState>());
	}
	
	if (input.IsPressed("inhale"))
	{
		
		player.ChangeState(std::make_unique<InhaleState>());
	}
	player.UpdatePhysics();
}
void HitState::Exit(Player& player)
{
#ifdef _DEBUG
	int rectColor = 0x0000ff;
	player.SetRectColor(rectColor);
#endif // _DEBUG
}

void InhaleState::Enter(Player& player)
{
	//画像をInhaleに変更
	player.SetGraph(player.GetImages().inhale);
	//吸い込みオブジェクトの生成をリクエストする
	player.SetGenerateInhale(true);
	//横方向のvelocityを0にする
	player.SetVelocity({ 0.0f,player.GetVelocity().y});
}

void InhaleState::Update(Player& player, Input& input)
{
	//ボタンを離したら吸い込みを終わる
	if (!input.IsPressed("inhale"))
	{
		player.ChangeState(std::make_unique<IdleState>());
	}

	player.UpdatePhysics();
}

void InhaleState::Exit(Player& player)
{
	//吸い込みオブジェクトの削除をリクエストする
	player.SetDeleteInhale(true);
}

void MouthHoldState::Enter(Player& player)
{
}

void MouthHoldState::Update(Player& player, Input& input)
{
}

void MouthHoldState::Exit(Player& player)
{
}
