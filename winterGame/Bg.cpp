#include "Bg.h"
#include <DxLib.h>
#include"Application.h"
#include "Player.h"
#include"Camera.h"
Bg::Bg(int skyGraphHandle,int cloudGraphHandle,int sunGraphHandle,float defaultPos):
	skyGraphHandle_(skyGraphHandle),
	cloudGraphHandle_(cloudGraphHandle),
	sunGraphHandle_(sunGraphHandle),
	scrollX_(defaultPos)
{
}

Bg::~Bg()
{
}

void Bg::Init(int defaultPos)
{
	scrollX_ = defaultPos;
}

void Bg::Update(Player& player,Camera& camera)
{
	auto wsize = Application::GetInstance().GetWindowSize();
	auto pPos = player.GetPosition();
	auto cPos = camera.GetPosition();
	scrollX_ = ((cPos.x - wsize.w * 0.5f) * 0.5f);

	if (scrollX_ < 0)
	{
		scrollX_ = 0;
	}
}

void Bg::Draw(int stageNo)
{
	auto wsize = Application::GetInstance().GetWindowSize();
	DrawRectRotaGraph(wsize.w / 2, wsize.h / 2, 0, 0, 640, 360, 3.0, 0.0, skyGraphHandle_, FALSE);
	if (stageNo != 3)
	{
		DrawGraph(200, 70, sunGraphHandle_, TRUE);
	}
	for (int i = 0; i < 4; i++)
	{
		DrawRectRotaGraph((i * 640 * 3) - scrollX_, wsize.h * 0.6, 0, 0, 640, 360, 3.0, 0.0, cloudGraphHandle_, TRUE);
	}
}
