#pragma once
class Player;
class Camera;
class Bg
{
	public:
	Bg(int skyGraphHnalde,int cloudGraphHandle,int sunGraphHandle,float defaultPos);
	~Bg();
	void Init(int defaultPos);
	void Update(Player& player,Camera& camera);
	void Draw();

private:
	int skyGraphHandle_;
	int cloudGraphHandle_;
	int sunGraphHandle_;
	float scrollX_;
};

