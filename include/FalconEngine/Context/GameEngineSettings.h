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
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineSettings();
    virtual ~GameEngineSettings() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    GameEngineGraphicsSettingsSharedPtr mGraphics;
    double                              mGraphicsMillisecondPerRender = 16.66666666666;
    GameEngineInputSettingsSharedPtr    mInput;
};
#pragma warning(default: 4251)

}
