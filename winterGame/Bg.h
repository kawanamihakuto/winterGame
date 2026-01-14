#pragma once
class Player;
class Camera;
class Bg
{
	public:
	Bg(int skyGraphHnalde,int cloudGraphHandle,float defaultPos);
	~Bg();
	void Init();
	void Update(Player& player,Camera& camera);
	void Draw();

private:
	int skyGraphHandle_;
	int cloudGraphHandle_;

	float scrollX_;
};

