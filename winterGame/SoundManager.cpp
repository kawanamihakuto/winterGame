#include "SoundManager.h"
#include<DxLib.h>
void SoundManager::Init()
{
	
}

void SoundManager::Update()
{
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

	if (currentBGM_ != -1)
	{
		StopSoundMem(currentBGM_);
	}

	currentBGM_ = it->second;
	PlaySoundMem(currentBGM_, loop ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK);
}

void SoundManager::StopBGM()
{
}

void SoundManager::FadeOutBGM(int frame)
{
	fadeFrame_ = frame;
	fadeTimer_ = frame;
}

void SoundManager::PlaySE(const std::string& name)
{
	auto it = seHandles_.find(name);
	if (it == seHandles_.end())
	{
		return;
	}

	PlaySoundMem(it->second, DX_PLAYTYPE_BACK);
}
