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
	//チェックを行う関数
	bool Check();
};

