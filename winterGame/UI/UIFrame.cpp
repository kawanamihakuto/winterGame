#include "UIFrame.h"
#include"Application.h"
#include<DxLib.h>
UIFrame::UIFrame(int graphHandle):
	graphHandle_(graphHandle)
{
}

UIFrame::~UIFrame()
{
}

void UIFrame::Init()
{

}

void UIFrame::Update()
{

}

void UIFrame::Draw()
{
	auto wsize = Application::GetInstance().GetWindowSize();
	int srcX, srcY;
	GetGraphSize(graphHandle_, &srcX, &srcY);
	DrawRectRotaGraph(wsize.w * 0.5f,wsize.h * 0.5f,0,0, srcX, srcY,1.0,0.0,graphHandle_,true);
}
