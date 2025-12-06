#include "Stage.h"
#include<DxLib.h>
#include<cassert>
#include<algorithm>
#include"StageData.h"
#include <fstream>
#include <sstream>
#include <cstdio>
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
    //CSVファイルを開く
    std::ifstream ifs(path);
    if (!ifs)
    {
        assert(false && "Stage CSV not found");
        return false;
    }
    //一行分の文字列
    std::string line;
    //横マス数
    int width = 0;
    //縦マス数
    int height = 0;
    //一行ずつ読み込む
    while (std::getline(ifs, line))
    {
        std::stringstream ss(line);
        std::string cell;
        int x = 0;
        //カンマ区切りで数値を読む
        while (std::getline(ss, cell, ','))
        {
            //文字列→数値に変換して格納
            data_.push_back(static_cast<uint16_t>(std::stoi(cell)));
            x++;
        }
        //最初の行で横サイズを決定
        if (width == 0)
            width = x;

        height++;
    }
    //マップサイズを保存
    size_ = { width, height };
    return true;
}

uint16_t Stage::GetData(int xidx, int yidx)const
{
    //範囲チェック
    assert(xidx >= 0 && xidx < size_.w);
    assert(yidx >= 0 && yidx < size_.h);
    //2次元→１次元変換
    return data_[yidx * size_.w + xidx];
}

Size Stage::MapSize()const
{
    return size_;
}