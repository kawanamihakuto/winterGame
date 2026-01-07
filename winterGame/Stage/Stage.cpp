#include "Stage.h"
#include<algorithm>
#include<DxLib.h>
#include<cassert>
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

struct TileCollision
{
    Rect rect;
};

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
    enemySpawns_.clear();
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
            int chip = std::stoi(cell);

            if (chip == 18)
            {
                EnemySpawn enemySpawn = { 18,Vector2{ static_cast<float>(x * kTileWorldSize) ,static_cast<float>(height_ * kTileWorldSize) } };
                enemySpawns_.push_back(enemySpawn);
                data_.push_back(static_cast < uint16_t>(0));
            }
            else if (chip == 27)
            {
                EnemySpawn enemySpawn = { 27,Vector2{ static_cast<float>(x * kTileWorldSize) ,static_cast<float>(height_ * kTileWorldSize) } };
                enemySpawns_.push_back(enemySpawn);
                data_.push_back(static_cast <uint16_t>(0));
            }
            else
            {
                //文字列→数値に変換して格納
                data_.push_back(static_cast<uint16_t>(chip));
            }
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

std::vector<Rect> Stage::GetSolidTiles(const Rect& objRect) const
{
    std::vector<Rect>result;

    //オブジェクトのRectを
    //どのタイル範囲にかかっているかに変換
    int leftTile = objRect.left_ / kTileWorldSize;
    int rightTile = (objRect.right_ -1) / kTileWorldSize;
    int topTile = objRect.top_ / kTileWorldSize;
    int bottomTile = (objRect.bottom_-1) / kTileWorldSize;
    //範囲補正
    leftTile = (std::max)(0, leftTile);
    topTile = (std::max)(0, topTile);
    rightTile = (std::min)(width_ - 1, rightTile);
    bottomTile = (std::min)(height_ - 1, bottomTile);

    //指定された範囲のタイルをチェック
    for (int ty = topTile; ty <= bottomTile; ty++)
    {
        for (int tx = leftTile; tx <= rightTile; tx++)
        {
            //タイルID取得
            int tileId = GetData(tx, ty);

            //0なら当たり判定なし
            if (tileId == 0)
            {
                continue;
            }

            //Rectを作る
            Rect tileRect;
            tileRect.SetCenter(
                tx * kTileWorldSize + kTileWorldSize * 0.5f,
                ty * kTileWorldSize + kTileWorldSize * 0.5f,
                kTileWorldSize,
                kTileWorldSize
            );
            result.push_back(tileRect);
        }
    }
    return result;
}

bool Stage::IsCollision(Rect rect, Rect& chipRect)const
{
    for (int y = 0; y < height_; y++)
    {
        for (int x = 0; x < width_; x++)
        {
            //タイルID取得
            int tileId = GetData(x, y);

            if (tileId == 0)
            {
                continue;
            }

            int chipLeft = static_cast<int>(x * kTileWorldSize);
            int chipRight = static_cast<int>(chipLeft + kTileWorldSize);
            int chipTop = static_cast<int>(y * kTileWorldSize);
            int chipBottom = static_cast<int>(chipTop + kTileWorldSize);

            //絶対に当たらない場合
            if (chipLeft > rect.GetRight())continue;
            if (chipTop > rect.GetBottom())continue;
            if (chipRight < rect.GetLeft())continue;
            if (chipBottom < rect.GetTop())continue;

            //ぶつかったマップチップの短形を設定する
            chipRect.left_ = static_cast<float>(chipLeft);
            chipRect.right_ = static_cast<float>(chipRight);
            chipRect.top_ = static_cast<float>(chipTop);
            chipRect.bottom_ = static_cast<float>(chipBottom);

            //いずれかのチップに当たっていたら終了する
            return true;
        }
    }
    return false;
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
            if (posX < 0 - kTileWorldSize) continue;
            if (posX > kScreenWidth) continue;
            if (posY < 0 - kTileWorldSize) continue;
            if (posY > kScreenHeight) continue;

            // 設置するチップ
            int chipNo = GetData(x,y);
            if (chipNo == 0) continue;
         
            Vector2 worldPos{ x * kTileWorldSize,y * kTileWorldSize };
            Vector2 screen = camera.WorldToScreen(worldPos);

            if (screen.x < -kTileWorldSize || screen.x > kScreenWidth) continue;
            if (screen.y < -kTileWorldSize || screen.y > kScreenHeight) continue;

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

const std::vector<EnemySpawn>& Stage::GetEnemySpawns() const
{
    return enemySpawns_;
}
