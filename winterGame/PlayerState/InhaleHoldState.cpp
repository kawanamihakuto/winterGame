#include "InhaleHoldState.h"
#include"Player.h"
#include"IdleState.h"
#include"GameScene.h"
void PlayerState::InhaleHoldState::Enter(Player& player)
{
}

void PlayerState::InhaleHoldState::Update(Player& player, Input& input)
{
	//吸い込み状態の継続がfalseになったら
	if (!player.GetIsInhaledHold())
	{
		player.SetMouthState(MouthState::holdingEnemy);
		player.SetStarOrAir(StarOrAir::star);
		player.GetScene()->PushRequest({ SceneRequestType::PlaySE,0.0f,0,"inhaleSuccess" });
		player.ChangeState(std::make_unique<IdleState>());
	}
}

void PlayerState::InhaleHoldState::Exit(Player& player)
{
	//吸い込みオブジェクトの削除をリクエストする
	player.EndInhale();
}
