#pragma once
#include "Base/Shot.h"
class AirShot :public Shot
{
public:
	AirShot(bool isRight,Vector2 pos, int graphHandle);
	virtual ~AirShot();

	void Init()override;
	void Init(std::shared_ptr<Player>player)override;
	void Update()override;
	void Update(std::shared_ptr<Player>player, std::vector<std::shared_ptr<EnemyBase>>enemies)override;
	void Draw()override;
	void Draw(Camera& camera)override;

	//マップタイルと当たった時の処理を行う関数
	void OnCollisionTile(const Rect& tileRect)override;

private:
	//生きている時間のカウント
	int count_;
};

