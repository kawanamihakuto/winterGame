#pragma once
#include"../System/Geometry.h"
/// <summary>
/// ’ZŒa‚ğŠÇ—‚·‚éƒNƒ‰ƒX
/// </summary>
class Rect
{
public:
	Rect();
	~Rect();
	/// <summary>
	/// ’ZŒa‚Ì•`‰æ
	/// </summary>
	/// <param name="color">’ZŒa‚ÌF</param>
	/// <param name="isFill">‘¾‚³</param>
	void Draw(unsigned int color, bool isFill)const;
	/// <summary>
	/// ¶ãÀ•W‚Æ•A‚‚³‚ğw’è
	/// </summary>
	/// <param name="left">¶</param>
	/// <param name="top">ã</param>
	/// <param name="width">•</param>
	/// <param name="height">‚‚³</param>
	void SetLT(float left, float top, float width, float height);
	/// <summary>
	/// ’†SÀ•W‚Æ•‚‚³‚ğw’è
	/// </summary>
	/// <param name="x">’†S‚ÌxÀ•W</param>
	/// <param name="y">’†S‚ÌyÀ•W</param>
	/// <param name="width">•</param>
	/// <param name="height">‚‚³</param>
	void SetCenter(float x,float y, float width,float height);
	/// <summary>
	/// ’ZŒa‚Ì•‚ğæ“¾
	/// </summary>
	/// <returns>’ZŒa‚Ì•</returns>
	float GetWidth()const;
	/// <summary>
	/// ’ZŒa‚Ì‚‚³‚ğæ“¾
	/// </summary>
	/// <returns>’ZŒa‚Ì‚‚³</returns>
	float GetHeight()const;
	/// <summary>
	/// ’ZŒa‚Ì’†SÀ•W‚ğæ“¾
	/// </summary>
	/// <returns>’ZŒa‚Ì’†SÀ•W</returns>
	Vector2 GetCenter()const;
	/// <summary>
	/// ’ZŒa‚Ì¶ã‚ÌxÀ•W‚ğæ“¾
	/// </summary>
	/// <returns>¶ã‚ÌxÀ•W</returns>
	float GetLeft()const { return left_; }
	/// <summary>
	/// ’ZŒa‚Ì¶ã‚ÌyÀ•W‚ğæ“¾
	/// </summary>
	/// <returns>¶ã‚ÌyÀ•W</returns>
	float GetTop()const { return top_; }
	/// <summary>
	/// ’ZŒa‚Ì‰E‰º‚ÌxÀ•W‚ğæ“¾
	/// </summary>
	/// <returns>‰E‰º‚ÌxÀ•W</returns>
	float GetRight()const { return right_; }
	/// <summary>
	/// ’ZŒa‚Ì‰E‰º‚ÌyÀ•W‚ğæ“¾
	/// </summary>
	/// <returns>‰E‰º‚ÌyÀ•W‚ğæ“¾</returns>
	float GetBottom()const { return bottom_; }
	/// <summary>
	/// ’ZŒa‚Ì“–‚½‚è”»’è
	/// </summary>
	/// <param name="rect">’ZŒaî•ñ</param>
	/// <returns>“–‚½‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©</returns>
	bool IsCollision(const Rect& rect);

public:
	//¶ã‚ÌxÀ•W
	float left_;
	//¶ã‚ÌyÀ•W
	float top_;
	//‰E‰º‚ÌxÀ•W
	float right_;
	//‰E‰º‚ÌyÀ•W
	float bottom_;
};