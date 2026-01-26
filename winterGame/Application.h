#pragma once
#include"Geometry.h"
#include<memory>
/// <summary>
/// アプリケーション全体を管理する
/// シングルトンクラス
/// </summary>
class SoundManager;
class Application
{
private:
	Size windowSize_;
	std::unique_ptr<SoundManager>sound_;

	Application();//newも変数宣言もできなくする
	Application(const Application& app) = delete;//コピーコンストラタも無効にする
	void operator = (const Application& app) = delete;//代入も無効にする
public:
	~Application();

	/// <summary>
	/// アプリケーションのシングルトンインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static Application& GetInstance();
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns>初期化成功:true/初期化失敗:false</returns>
	bool Init();

	/// <summary>
	/// アプリケーションをスタートする
	/// ゲームループを内包する
	/// </summary>
	void Run();

	/// <summary>
	/// アプリケーション終了処理
	/// </summary>
	void Terminate();

	/// <summary>
	/// ウィンドウのサイズを取得
	/// </summary>
	/// <returns></returns>
	const Size& GetWindowSize()const;
	/// <summary>
	/// サウンドマネージャーを取得
	/// </summary>
	/// <returns></returns>
	SoundManager& GetSound();
};

