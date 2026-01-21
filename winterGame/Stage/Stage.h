#pragma once
#include"System/Geometry.h"
#include<vector>
#include<string>
#include"../Collision/Rect.h"
struct TileCollision;
class Camera;

struct EnemySpawn
{
	int type;
	Vector2 pos;
	bool isRight;
};

/// <summary>
/// ステージデータを管理するクラス
/// </summary>
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
	//当たる可能性があるRectを返す
	std::vector<Rect>GetSolidTiles(const Rect& objRect)const;
	//マップチップの当たり判定
	bool IsCollision(Rect rect, Rect& chipRect)const;

	void Draw(Camera& camera);

	const std::vector<EnemySpawn>& GetEnemySpawns()const;
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

	std::vector<EnemySpawn>enemySpawns_;
};

