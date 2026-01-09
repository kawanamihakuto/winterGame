#include "Lerp.h"
#include<cmath>
Lerp::Lerp()
{
}
Lerp::~Lerp()
{
}
Vector2 Lerp::VLerp(const Vector2 stert, const Vector2 end, float t)
{
    Vector2 ret;
    ret.x = std::lerp(stert.x,end.x,t);
    ret.y = std::lerp(stert.y,end.y,t);

    return ret;
}

float Lerp::FLerp(const float stert, const float end, float t)
{
    float ret;
    ret = std::lerp(stert, end, t);
    return ret;
}
