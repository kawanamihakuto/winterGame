#pragma once
#include<string>
#include<map>
class ImageManager
{
private:
	//newも変数宣言もできなくなる
	ImageManager();
	//コピーコンストラクタを無効にする
	ImageManager(const ImageManager& imgManager) = delete;
	//代入を無効にする
	void operator = (const ImageManager& imgManager) = delete;

	std::map<std::string, int>images_;
public:
	~ImageManager();
	/// <summary>
	/// イメージマネージャーのシングルトンインスタンスを取得
	/// </summary>
	/// <returns></returns>
	static ImageManager& GetInstance();
	/// <summary>
	/// 画像をロード
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	int LoadImg(const std::string&key,const std::string& filePath);
	/// <summary>
	/// 画像ハンドルを取得
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	int GetImg(const std::string& key);
	/// <summary>
	/// 画像を開放(1枚だけ)
	/// </summary>
	/// <param name="key"></param>
	void Release(const std::string& key);
	/// <summary>
	/// 全画像を開放
	/// </summary>
	void ReleaseAll();
};

