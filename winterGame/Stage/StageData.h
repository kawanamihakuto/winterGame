#pragma once
#include<algorithm>
#pragma pack(push,1)
//データ配列に必要な情報
struct DataSetting
{
	//チップ幅
	uint8_t chipW;
	//チップ高さ
	uint8_t chipH;
	//レイヤー数
	uint8_t layerCount;
	//1チップに何ビット使用しているのか
	uint8_t bitCount;
};

//マップデータのヘッダ
struct DataHeader
{
	//正しければ'FMF_'になってる
	char identifier[4];
	//データのサイズ
	uint32_t size;
	//データの幅
	uint32_t width;
	//データの高さ
	uint32_t height;
	//データ配列に必要な情報
	DataSetting setting;
};

#pragma pack(pop)