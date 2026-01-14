#pragma once
class UIFrame
{
public:
	UIFrame(int graphHandle);
	~UIFrame();
	void Init();
	void Update();
	void Draw();
private:
	int graphHandle_;
};

