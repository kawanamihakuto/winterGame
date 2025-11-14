#pragma once
/// <summary>
/// 2Dベクトルクラス
/// </summary>
struct Vector2
{
	float x, y;
	float Length()const;//ベクトルの大きさを取る
	void Normalize();//正規化
	Vector2 Normalized()const;
	Vector2 operator-()const;
	void operator+=(const Vector2& val);//加算
	void operator-=(const Vector2& val);//減算
	void operator*=(const float scale);//ベクトルをn倍する
	Vector2 operator+(const Vector2& val)const;//加算
	Vector2 operator-(const Vector2& val)const;//減算
	Vector2 operator*(float scale)const;//ベクトルの累乗
};

using position2 = Vector2;//座標もベクトルとして扱う

/// <summary>
/// 2Dのサイズを定義する構造体
/// </summary>
struct Size
{
	int w;//幅
	int h;//高さ
};