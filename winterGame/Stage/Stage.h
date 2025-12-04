#pragma once
#include"System/Geometry.h"
#include<vector>
/// <summary>
/// ステージデータを管理するクラス
/// </summary>
class Stage
{
	//データサイズ
	Size dataSize_;
	//データ本体
	std::vector<uint16_t>data_;
public:
	void Load(int stageNo);
	Size MapSize()const;
	uint8_t GetData(int xidx, int yidx)const;
	const std::vector<uint16_t>& GetAllData()const;
};

