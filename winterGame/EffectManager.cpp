#include "EffectManager.h"
#include"Camera.h"
#include<DxLib.h>

namespace
{
	constexpr int kFrameMax = 17;
}

EffectManager::EffectManager(int graphHandle):
	graphHandle_(graphHandle)
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
	
}

void EffectManager::Update()
{
	auto it = std::remove_if(effects_.begin(),
		effects_.end(),
		[](std::shared_ptr<Effect> effect)
		{
			return !effect->isAlive;
		});
	effects_.erase(it, effects_.end());
}

void EffectManager::Draw(Camera& camera)
{
	for (auto effect : effects_)
	{
		auto screen = camera.WorldToScreen(effect->pos);
		effect->size += 0.2;
		effect->angle += 0.13;
		DrawRectRotaGraph(screen.x, screen.y, 0, 16, 16, 16, effect->size, effect->angle, graphHandle_, true);
		effect->frame++;
		if (effect->frame >= kFrameMax)
		{
			effect->isAlive = false;
		}
	}
}

void EffectManager::Generate(const Vector2& pos)
{
	effects_.push_back(std::make_shared<Effect>());
	effects_.back()->pos = pos;
}
