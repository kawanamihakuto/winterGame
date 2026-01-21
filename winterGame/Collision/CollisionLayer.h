#pragma once
#include<cstdint>

//ビットフラグとして使う型
using CollisionLayer = uint32_t;
/// <summary>
/// 当たり判定の役割をビットで表す
/// </summary>
namespace CollisionLayers
{
	//ビットで管理することで & を使い、複数指定を可能にする
	//ビットシフト
	//1<<n -> 1をnaビット左にずらす
	constexpr CollisionLayer kNone	 = 0;
	constexpr CollisionLayer kNormalPlayer = 1 << 0;
	constexpr CollisionLayer kEnemy	 = 1 << 1;
	constexpr CollisionLayer kInhale = 1 << 2;
	constexpr CollisionLayer kAttack = 1 << 3;
	constexpr CollisionLayer kInhaledPlayer = 1 << 4;
	constexpr CollisionLayer kDoor = 1 << 5;
	constexpr CollisionLayer kItem = 1 << 6;
}

