#include "SoundManager.h"
#include<DxLib.h>
#include<cassert>
SoundManager::SoundManager():
	fadeFrame_(0),
	fadeTimer_(0)
{
}
SoundManager::~SoundManager()
{
	for (auto se : seHandles_)
	{
		DeleteSoundMem(se.second);
	}

	for (auto bgm : bgmHandles_)
	{
		DeleteSoundMem(bgm.second);
	}
}
void SoundManager::Init()
{
	seHandles_["jump"] = LoadSoundMem("data/se/jump.wav");
	assert(seHandles_["jump"] > -1);
	seHandles_["starShot"] = LoadSoundMem("data/se/starShot.mp3");
	assert(seHandles_["starShot"] > -1);
	seHandles_["hovering"] = LoadSoundMem("data/se/hovering.mp3");
	assert(seHandles_["hovering"] > -1);
	seHandles_["inhaleSuccess"] = LoadSoundMem("data/se/inhaleSuccess.mp3");
	assert(seHandles_["inhaleSuccess"] > -1);
	seHandles_["inhale"] = LoadSoundMem("data/se/inhale.mp3");
	assert(seHandles_["inhale"] > -1);
	seHandles_["push"] = LoadSoundMem("data/se/push.mp3");
	assert(seHandles_["push"] > -1);
	seHandles_["enemyDead"] = LoadSoundMem("data/se/enemyDead.mp3");
	assert(seHandles_["enemyDead"] > -1);
	seHandles_["airShot"] = LoadSoundMem("data/se/airShot.mp3");
	assert(seHandles_["airShot"] > -1);
	seHandles_["playerDamage"] = LoadSoundMem("data/se/playerDamage.mp3");
	assert(seHandles_["playerDamage"] > -1);
	seHandles_["door"] = LoadSoundMem("data/se/door.mp3");
	assert(seHandles_["door"] > -1);
	seHandles_["Gameover"] = LoadSoundMem("data/se/Gameover.mp3");
	assert(seHandles_["Gameover"] > -1);
	seHandles_["playerDead"] = LoadSoundMem("data/se/playerDead.mp3");
	assert(seHandles_["playerDead"] > -1);
	seHandles_["bossDamage"] = LoadSoundMem("data/se/bossDamage.mp3");
	assert(seHandles_["bossDamage"] > -1);
	seHandles_["itemGet"] = LoadSoundMem("data/se/itemGet.wav");
	assert(seHandles_["itemGet"] > -1);
	seHandles_["bossShot"] = LoadSoundMem("data/se/bossShot.mp3");
	assert(seHandles_["bossShot"] > -1);
	seHandles_["bossExplosion"] = LoadSoundMem("data/se/bossExplosion.mp3");
	assert(seHandles_["bossExplosion"] > -1);
	
	bgmHandles_["titleBGM"] = LoadSoundMem("data/bgm/titleBGM.mp3");
	assert(bgmHandles_["titleBGM"] > -1);
	bgmHandles_["gameBGM"] = LoadSoundMem("data/bgm/gameBGM.mp3");
	assert(bgmHandles_["gameBGM"] > -1);
	bgmHandles_["gameoverBGM"] = LoadSoundMem("data/bgm/gameoverBGM.mp3");
	assert(bgmHandles_["gameoverBGM"] > -1);
}

void SoundManager::Update()
{
#ifdef _DEBUG
	DrawFormatString(16, 40, 0xffffff,
		"BGM=%d fadeTimer=%d", currentBGM_, fadeTimer_);
#endif // _DEBUG
	if (fadeTimer_ > 0 && currentBGM_ != -1)
	{
		float rate = static_cast<float>(fadeTimer_) / fadeFrame_;
		int volume = static_cast<int>(255 * rate);

		ChangeVolumeSoundMem(volume, currentBGM_);

		fadeTimer_--;
		if (fadeTimer_ == 0)
		{
			StopSoundMem(currentBGM_);
			currentBGM_ = -1;
		}
	}
}

void SoundManager::PlayBGM(const std::string& name, bool loop)
{
	auto it = bgmHandles_.find(name);
	if (it == bgmHandles_.end()) 
	{
		return; 
	}

	fadeTimer_ = 0;
	fadeFrame_ = 0;

	if (currentBGM_ != -1)
	{
		StopSoundMem(currentBGM_);
	}

	currentBGM_ = it->second;
	ChangeVolumeSoundMem(160, currentBGM_);
	PlaySoundMem(currentBGM_, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::StopBGM()
{
	if (currentBGM_ != -1)
	{
		StopSoundMem(currentBGM_);
		currentBGM_ = -1;
	}
}

void SoundManager::FadeOutBGM(int frame)
{
	fadeFrame_ = frame;
	fadeTimer_ = frame;
	if (currentBGM_ != -1)
	{
		SetVolumeSoundMem(255, currentBGM_);
	}
}

void SoundManager::PlaySE(const std::string& name,bool loop)
{
	
	auto it = seHandles_.find(name);
	if (it == seHandles_.end())
	{
		return;
	}
	if (loop)
	{
		PlaySoundMem(it->second, DX_PLAYTYPE_LOOP);
	}
	else
	{
		PlaySoundMem(it->second, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::StopSE(const std::string& name)
{
	auto it = seHandles_.find(name);
	if (it == seHandles_.end())
	{
		return;
	}
	StopSoundMem(it->second);
}