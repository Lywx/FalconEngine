#pragma once

#include <FalconEngine/Context/Header.h>

namespace FalconEngine
{

class GameEngineGraphicsSettings;
using GameEngineGraphicsSettingsSharedPtr = std::shared_ptr<GameEngineGraphicsSettings>;

class GameEngineInputSettings;
using GameEngineInputSettingsSharedPtr = std::shared_ptr<GameEngineInputSettings>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineSettings
{
public:
    GameEngineSettings();
    virtual ~GameEngineSettings() = default;

public:
    GameEngineGraphicsSettingsSharedPtr mGraphics;
    GameEngineInputSettingsSharedPtr    mInput;
};
#pragma warning(default: 4251)

}
