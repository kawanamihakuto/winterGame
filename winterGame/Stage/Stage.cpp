#include "Stage.h"
#include<DxLib.h>
#include<cassert>
#include<algorithm>
#include"StageData.h"
void Stage::Load(int stageNo)
{
    char filePath[256];
    sprintf_s(filePath, "data/stage%d.fmf", stageNo);

    int handle = FileRead_open(filePath);
    assert(handle != -1);

    // ① ヘッダを読む
    DataHeader header{};
    FileRead_read(&header, sizeof(header), handle);

    printfDx(
        "Header id=%.4s w=%u h=%u size=%u bitCount=%u layer=%u\n",
        header.identifier,
        header.width,
        header.height,
        header.size,
        header.setting.bitCount,
        header.setting.layerCount
    );

    // ★★★ ② ここ！！ ★★★
    int bytesPerChip = header.setting.bitCount / 8; // bitCount=16 → 2
    int oneLayerSize = header.width * header.height * bytesPerChip;

    FileRead_seek(
        handle,
        sizeof(DataHeader) + oneLayerSize * 0, // レイヤー0
        SEEK_SET
    );

    uint8_t raw[16]{};
    FileRead_read(raw, 16, handle);

    printfDx("raw bytes (layer0): ");
    for (int i = 0; i < 16; ++i)
        printfDx("%02X ", raw[i]);
    printfDx("\n");

    // ③ ここからが本番読み込み（後で直す）
    // ↓ 今はまだ書かなくていい
}

Size Stage::MapSize()const
{
	return dataSize_;
}

uint8_t Stage::GetData(int xidx, int yidx)const
{
	return data_[yidx * dataSize_.w + xidx];
}

const std::vector<uint16_t>& Stage::GetAllData() const
{
	return data_;
}
