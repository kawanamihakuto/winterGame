#include "BossBattleDeadAnimState.h"
#include"Player.h"
#include"GameScene.h"
namespace
{
	constexpr int kCountMax = 60;
}

void PlayerState::BossBattleDeadAnimState::Enter(Player& player)
{
	player.SetSize(6.1);
	player.SetVelocity({ 0,0 });
	player.SetCameraShakeRequest(true);
	isPlaySe_ = true;
}

void PlayerState::BossBattleDeadAnimState::Update(Player& player, Input& input)
{
	player.SetSize(6.1);
	if (count_++ >= kCountMax)
	{
		if (isPlaySe_)
		{
			player.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"playerDead" });
			isPlaySe_ = false;
		}
		auto pos = player.GetPosition();
		pos.x -= 10.0f;
		pos.y -= 10.0f;
		player.SetPosition(pos);
		auto angle = player.GetDeadAnimAngle();
		angle += 0.1;
		player.SetDeadAnimAngle(angle);
	}
}

void PlayerState::BossBattleDeadAnimState::Exit(Player& player)
{

}