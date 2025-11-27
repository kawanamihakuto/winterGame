#pragma once
#include<vector>
class GameObject;
class CollisionManager
{
public:
	//当たり判定を行いたいオブジェクトを追加する関数
	void Add(GameObject& object);
	//毎フレーム最初に呼んで登録をクリアする関数
	void Clear();
	//登録されたすべてのオブジェクトの当たり判定を行う関数
	void CheckAll();

private:
	//レイヤーの条件を満たしているかのチェックをする関数
	bool CanCollide(const GameObject& a, const GameObject& b)const;
	//登録されたオブジェクトを入れるvector
	std::vector<GameObject*> objects_;
};