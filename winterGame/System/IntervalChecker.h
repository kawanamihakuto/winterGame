#pragma once
/// <summary>
/// インターバル用クラス
/// </summary>
class IntervalChecker
{
private:
	int timer_;
	int interval_;

public:
	//引数でインターバルが何フレームかを受け取る
	IntervalChecker(int n);
	//カウントを進めてチェックを行う関数
	bool Check();
	//タイマーをリセットする関数
	void ResetTimer();
};

