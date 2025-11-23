#include "AirShot.h"

constexpr float kAirGraphCutRow = 5;

AirShot::AirShot(Vector2 pos, int graphHandle):Shot(pos,graphHandle)
{

}

AirShot::~AirShot()
{
}

void AirShot::Init()
{
}

void AirShot::Init(std::shared_ptr<Player> player)
{
}

void AirShot::Update()
{
}

void AirShot::Update(std::shared_ptr<Player> player, std::vector<std::shared_ptr<EnemyBase>> enemies)
{
}

void AirShot::Draw()
{
}

void AirShot::Draw(Camera& camera)
{
}
