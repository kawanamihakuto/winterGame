#pragma once
class Bg
{
	public:
	Bg(int graphHnalde);
	~Bg();
	void Init();
	void Update();
	void Draw();

private:
	int skyGraphHandle_;
};

