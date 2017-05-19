#pragma once

#include <FalconEngine/Context/Header.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineGraphicsSettings final
{
public:
    GameEngineGraphicsSettings(int width, int height);
    ~GameEngineGraphicsSettings() = default;

public:
    std::string mTitle;

    int         mWidth;
    int         mHeight;
    float       mNear = 0.0f;
    float       mFar = 1.0f;
};
#pragma warning(default: 4251)

using GameEngineGraphicsSettingsSharedPtr = std::shared_ptr<GameEngineGraphicsSettings>;

}
