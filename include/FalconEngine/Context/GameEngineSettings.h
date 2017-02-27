#pragma once

#include <FalconEngine/Context/ContextInclude.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineInputSettings.h>

namespace FalconEngine
{

class GameEngineSettings
{
public:
    GameEngineSettings();
    virtual ~GameEngineSettings() = default;

public:
    GameEngineGraphicsSettingsSharedPtr mGraphics;
    GameEngineInputSettingsSharedPtr    mInput;
};

using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;
}
