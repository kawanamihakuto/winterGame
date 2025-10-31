#pragma once
class Character
{
public:
	Character();
	virtual ~Character();

	virtual void Init() = 0;

	virtual void Update() = 0;
	
	virtual void Draw() = 0;
};

