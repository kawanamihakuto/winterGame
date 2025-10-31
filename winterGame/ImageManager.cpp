#include<DxLib.h>
#include "ImageManager.h"

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	ReleaseAll();
}

ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

int ImageManager::LoadImg(const std::string& name,const std::string& firePath)
{
	std::string data = "data";
	std::string slash = "/";
	int handle = LoadGraph((data + slash + name + slash + firePath).c_str());
	return handle;
}

void ImageManager::ReleaseAll()
{
}
