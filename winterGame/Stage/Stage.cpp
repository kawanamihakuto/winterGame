#include "Stage.h"
#include<DxLib.h>
#include<cassert>
#include<algorithm>
#include"StageData.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include"Game.h"
#include"Camera.h"
namespace
{
    constexpr int kChipNumX = 60;
    constexpr int kChipNumY = 20;
    constexpr int kChipSize = 16;
    constexpr int kTileSrcSize = 16;
    constexpr int kTileWorldSize = 16 * 3;
}

void Stage::Init(int graphHandle,int chipW,int chipH)
{
    tileGraph_ = graphHandle;
    chipW_ = chipW;
    chipH_ = chipH;
}

bool Stage::Load(int stageNo)
{
    char path[64];
    sprintf_s(path, "data/stage%02d.csv", stageNo);
  
    return LoadCsv(path);
}

bool Stage::LoadCsv(const std::string& path)
{
    //以前のステージデータを破棄
    data_.clear();
    size_ = { 0, 0 };
    width_ = 0;
    height_ = 0;
    //CSVファイルを開く
    std::ifstream ifs(path);
    if (!ifs)
    {
        assert(false && "Stage CSV not found");
        return false;
    }
    //一行分の文字列
    std::string line;
  
    //一行ずつ読み込む
    int y = 0;
    while (std::getline(ifs, line)&&y < kChipNumY)
    {
        std::stringstream ss(line);
        std::string cell;
        int x = 0;
        //カンマ区切りで数値を読む
        while (std::getline(ss, cell, ',')&& x < kChipNumX)
        {
            //文字列→数値に変換して格納
            data_.push_back(static_cast<uint16_t>(std::stoi(cell)));
            x++;
        }
        //最初の行で横サイズを決定
        if (width_ == 0)
            width_ = x;

        height_++;
    }
    //マップサイズを保存
    size_ = { width_, height_ };

    return true;
}

uint16_t Stage::GetData(int xidx, int yidx)const
{
    if (xidx < 0 || yidx < 0 || xidx >= width_ || yidx >= height_)
    {
        return 0;
    }

    int index = yidx * width_ + xidx;

    if (index < 0 || index >= (int)data_.size())
    {
        return 0;
    }

    return data_[index];
}

Size Stage::MapSize()const
{
    return size_;
}

void Stage::Draw(Camera& camera)
{
    int imgW, imgH;
    GetGraphSize(tileGraph_, &imgW, &imgH);
    int tilesPerRow = imgW / chipW_;
    // マップチップの描画
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            int posX = static_cast<int>(x * kChipSize);
            int posY = static_cast<int>(y * kChipSize);

            // 画面外は描画しない
            if (posX < 0 - kChipSize) continue;
            if (posX > kScreenWidth) continue;
            if (posY < 0 - kChipSize) continue;
            if (posY > kScreenHeight) continue;

            // 設置するチップ
            int chipNo = GetData(x,y);
            if (chipNo == 0) continue;
         
            Vector2 worldPos{ x * kTileWorldSize,y * kTileWorldSize };
            Vector2 screen = camera.WorldToScreen(worldPos);

            if (screen.x < -chipW_ || screen.x > kScreenWidth) continue;
            if (screen.y < -chipH_ || screen.y > kScreenHeight) continue;

            // マップチップのグラフィック切り出し座標
            int srcX = (chipNo % tilesPerRow) * kTileSrcSize;
            int srcY = (chipNo / tilesPerRow) * kTileSrcSize;

            DrawRectExtendGraph(screen.x, screen.y,
                screen.x+kTileWorldSize, screen.y+kTileWorldSize,
                srcX, srcY,
                kTileSrcSize, kTileSrcSize,
                tileGraph_, true);
        }
    }
}