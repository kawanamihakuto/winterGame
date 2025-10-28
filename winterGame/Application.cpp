#include "Application.h"

constexpr int kDefaultWindowWidth = 640;//デフォルトウィンドウ幅
constexpr int kDefaultWindowHeight = 480;//デフォルトウィンドウ高さ
constexpr int kDefaultColorBit = 32;//デフォルトカラービット

Application::Application():
	windowSize_{kDefaultWindowWidth,kDefaultWindowHeight}
{

}
