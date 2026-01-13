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

	DrawRectRotaGraph(wsize.w / 2,wsize.h - 70,0,0,64,30,5.0,0.0,graphHandle_,true);
}
