#pragma once
#include"Stage.h"
class Camera;
class TileMapRenderer
{
public:
	TileMapRenderer(int tileGraph, int chipW, int chipH);

	void Draw(const Stage& stage,Camera& camera);
private:
	int tileGraph_;
	int chipW_;
	int chipH_;
};

