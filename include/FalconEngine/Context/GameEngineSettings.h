#pragma once

#include <FalconEngine/ContextInclude.h>

namespace FalconEngine
{

class GameEngineGraphicsSettings;
using GameEngineGraphicsSettingsSharedPtr = std::shared_ptr<GameEngineGraphicsSettings>;

class GameEngineInputSettings;
using GameEngineInputSettingsSharedPtr = std::shared_ptr<GameEngineInputSettings>;

class GameEngineSettings
{
public:
    GameEngineSettings();
    virtual ~GameEngineSettings() = default;

public:
    GameEngineGraphicsSettingsSharedPtr mGraphics;
    GameEngineInputSettingsSharedPtr    mInput;
};

}
