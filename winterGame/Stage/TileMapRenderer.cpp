#include "TileMapRenderer.h"
#include<DxLib.h>
#include<memory>
#include"Camera.h"
TileMapRenderer::TileMapRenderer(int tileGraph, int chipW, int chipH):
tileGraph_(tileGraph),
chipW_(chipW),
chipH_(chipH)
{
}

void TileMapRenderer::Draw(const Stage& stage,Camera& camera)
{
	const Size mapSize = stage.MapSize();

	Size size = stage.MapSize();
	char buf[64];
	sprintf_s(buf, "W:%d H:%d", size.w, size.h);
//	DrawString(0, 20, buf, GetColor(255, 255, 0));

	int imgW, imgH;
	GetGraphSize(tileGraph_, &imgW, &imgH);
	int tilesPerRow = imgW / chipW_;

	for (int y = 0; y < mapSize.h; y++)
	{
		for (int x = 0; x < mapSize.w; x++)
		{
			int chipNo = stage.GetData(x, y);

			int srcX = (chipNo % tilesPerRow) * chipW_;
			int srcY = (chipNo / tilesPerRow) * chipH_;
			if (chipNo == 0)
			{
				continue;
			}
			printfDx("cam %d %d\n",
				camera.GetDrawOffset().x,
				camera.GetDrawOffset().y);
			DrawRectGraph(x * chipW_  + camera.GetDrawOffset().x, y * chipH_ +camera.GetDrawOffset().y,
				srcX, srcY,
				chipW_, chipH_,
				3.0,3.0,
				tileGraph_, true);
		}
	}
}
