#pragma once

#include <FalconEngine/ContextInclude.h>

namespace FalconEngine
{

class GameEngineGraphicsSettings sealed
{
public:
    GameEngineGraphicsSettings();
    ~GameEngineGraphicsSettings() = default;

public:
    std::string mTitle;

    int         mWidth;
    int         mHeight;
};

using GameEngineGraphicsSettingsSharedPtr = std::shared_ptr<GameEngineGraphicsSettings>;

}
