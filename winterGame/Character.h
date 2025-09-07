#pragma once
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init();

	virtual void Update();
	
	virtual void Draw();
};

