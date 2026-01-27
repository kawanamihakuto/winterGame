#pragma once
#include<unordered_map>
#include<string>
class SoundManager
{
public:
	void Init();
	void Update();

	//BGM
	void PlayBGM(const std::string& name,bool loop = true);
	void StopBGM();
	void FadeOutBGM(int frame);

	//SE
	void PlaySE(const std::string& name,bool loop);
	void StopSE(const std::string& name);
private:
	std::unordered_map<std::string, int>bgmHandles_;
	std::unordered_map<std::string, int>seHandles_;

	int currentBGM_ = -1;

	// フェード用
	int fadeFrame_ = 0;
	int fadeTimer_ = 0;
};

