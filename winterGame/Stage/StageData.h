#pragma once
#include<algorithm>
#pragma pack(push,1)
//データ配列に必要な情報
struct DataSetting
{
	//1チップに何ビット使用しているのか
	uint8_t bitCount;
	//レイヤー数
	uint8_t layerCount;
};

//マップデータのヘッダ
struct DataHeader
{
	//正しければ'FMF_'になってる
	char identifier[4];
	//データの幅
	uint32_t width;
	//データの高さ
	uint32_t height;
	//データのサイズ
	uint32_t size;
	//データ配列に必要な情報
	DataSetting setting;
};

#pragma pack(pop)