#include "CollisionManager.h"
#include"GameObject.h"
#include"../Stage/Stage.h"
void CollisionManager::Add(GameObject& object)
{
	//アドレスだけ保持
	objects_.push_back(&object);
}

void CollisionManager::Clear()
{
	//前のフレームの登録をクリアする
	objects_.clear();
}

void CollisionManager::CheckAll()
{
	//総当たり判定を行う
	//.size()の戻り値の型がsize_tなのでint ではなく size_t
	for (size_t i = 0; i < objects_.size(); i++)
	{
		for (size_t j = i + 1; j < objects_.size(); j++)
		{
			GameObject& a = *objects_[i];
			GameObject& b = *objects_[j];
			//レイヤーを見て当たるかどうかをチェック
			if (!CanCollide(a, b))
			{
				continue;
			}
			//当たっているか判定
			if (a.GetColliderRect().IsCollision(b.GetColliderRect()))
			{
				//aとbに当たったことを伝える
				a.OnCollision(b);
				b.OnCollision(a);
			}
		}
	}
}

void CollisionManager::CheckMapCollision(const Stage& stage)
{
	//登録されたすべてのオブジェクトに対して衝突チェック
	for (auto& obj : objects_)
	{
		//マップと当たりたいかどうかをチェック
		if (!obj->IsMapCollision())
		{
			continue;
		}
		//オブジェクトの当たり判定を取得
		Rect objRect = obj->GetColliderRect();
		//当たる可能性があるタイルのRectを取得
		auto tileRects = stage.GetSolidTiles(objRect);

		//tileRects分回す
		for (const auto& tileRect : tileRects)
		{
			//Rect同士が当たっていないなら無視する
			if (!objRect.IsCollision(tileRect))
			{
				continue;
			}
			//オブジェクトに処理を任せる
			obj->OnCollisionTile(tileRect);

			//処理をした後のRectをとる
			objRect = obj->GetColliderRect();
		}
	}
}

bool CollisionManager::CanCollide(const GameObject& a, const GameObject& b) const
{
	//aがbに当たるかどうか判定
	// AND演算の結果0なら
	if ((a.GetHitMask() & b.GetCollisionLayer()) == 0)
	{
		//aはbにあたらない
		return false;
	}
	//bがaに当たるかどうか判定
	//AND演算の結果0なら
	if ((b.GetHitMask() & a.GetCollisionLayer()) == 0)
	{
		//bはaにあたらない
		return false;
	}

	//当たる必要があるならtrueを返して当たっているかの判定をする
	return true;
}
