#include "BossBattleDeadAnimState.h"
#include"Player.h"
namespace
{
	constexpr int kCountMax = 60;
}

void PlayerState::BossBattleDeadAnimState::Enter(Player& player)
{
	player.SetSize(6.1);
	player.SetVelocity({ 0,0 });
	player.SetCameraShakeRequest(true);
}

void PlayerState::BossBattleDeadAnimState::Update(Player& player, Input& input)
{
	player.SetSize(6.1);
	if (count_++ >= kCountMax)
	{
		
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