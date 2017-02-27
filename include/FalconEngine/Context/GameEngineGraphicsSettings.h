#pragma once

#include <FalconEngine/Context/ContextInclude.h>

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
