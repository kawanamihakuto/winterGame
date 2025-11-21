#include "InhaleHoldState.h"
#include"../Player.h"
#include"IdleState.h"
void PlayerState::InhaleHoldState::Enter(Player& player)
{
}

void PlayerState::InhaleHoldState::Update(Player& player, Input& input)
{
	//吸い込み状態の継続がfalseになったら
	if (!player.GetIsInhaledHold())
	{
		player.SetMouthState(MouthState::Holding);
		player.ChangeState(std::make_unique<IdleState>());
	}
	player.UpdatePhysics();
}

void PlayerState::InhaleHoldState::Exit(Player& player)
{
	//吸い込みオブジェクトの削除をリクエストする
	player.SetDeleteInhale(true);
}
