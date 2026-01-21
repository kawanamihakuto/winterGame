#pragma once
#include "Item.h"
#include<memory>
class Player;
class BossItem : public Item
{
public:
	BossItem(std::shared_ptr<Player>player,Vector2 pos,int graphHandle);
	~BossItem();
	void Init()override;
	void Init(int stageNo) ;
	void Update()override ;
	void Draw()override ;
	void Draw(Camera& camera);
private:
	int graphHandle_;
	float frame_;
};

