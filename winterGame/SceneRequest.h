#pragma once
#include <string>

enum class SceneRequestType
{
    CameraShake,
    PlaySE,
    StopSE,
    StopBGM
};

struct SceneRequest
{
    SceneRequestType type;

    // 汎用パラメータ
    float f0 = 0.0f;
    int   i0 = 0;
    std::string s0;
    bool loop = false;
};