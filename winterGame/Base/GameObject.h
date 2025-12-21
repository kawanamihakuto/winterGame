#pragma once
#include"Geometry.h"
#include"Rect.h"
#include"CollisionLayer.h"

struct TileCollision;
/// <summary>
/// ゲーム全体のオブジェクト基底クラス
/// </summary>
class GameObject
{
public:
	GameObject(const Vector2 pos );
	
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	//当たり判定の形を返すゲッター
	virtual Rect GetColliderRect()const = 0;
	//自身のレイヤーを返すゲッター
	virtual CollisionLayer GetCollisionLayer()const = 0;
	//当たりたいレイヤーを返すゲッター
	virtual CollisionLayer GetHitMask()const = 0;
	//当たった時の処理を行う関数
	virtual void OnCollision(GameObject& other) = 0;
	//ポジションのゲッター
	const Vector2& GetPosition()const { return position_; }

protected:
	//Vector2でポジションを管理
	Vector2 position_;
	//当たり判定用の矩形
	Rect rect_;
};