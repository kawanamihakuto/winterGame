#pragma once
#include"System/Geometry.h"
#include<vector>
#include<string>
/// <summary>
/// ステージデータを管理するクラス
/// </summary>
class Camera;
class Stage
{
public:
	void Init(int graphHandle,int chipW,int chipH);

	//ステージ番号からSCVを読み込む
	bool Load(int stageNo);
	//指定したマスのタイル番号を取得
	uint16_t GetData(int x, int y)const;
	//マップ全体のサイズ取得
	Size MapSize()const;

	void Draw(Camera& camera);
private:
	//CSVを読み込んでマップデータを作る
	bool LoadCsv(const std::string& path);

	Size size_;
	std::vector<uint16_t>data_;
	int width_;
	int height_;
	int tileGraph_;
	int chipW_;
	int chipH_;
};

