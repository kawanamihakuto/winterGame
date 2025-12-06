#pragma once
#include"System/Geometry.h"
#include<vector>
#include<string>
/// <summary>
/// ステージデータを管理するクラス
/// </summary>
class Stage
{
public:
	//ステージ番号からSCVを読み込む
	bool Load(int stageNo);
	//指定したマスのタイル番号を取得
	uint16_t GetData(int x, int y)const;
	//マップ全体のサイズ取得
	Size MapSize()const;
private:
	//CSVを読み込んでマップデータを作る
	bool LoadCsv(const std::string& path);

	Size size_;
	std::vector<uint16_t>data_;
};

