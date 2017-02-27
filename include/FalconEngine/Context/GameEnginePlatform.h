#pragma once

#include <FalconEngine/Context/ContextInclude.h>

#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

class GameEngineData;
class GameEnginePlatform
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEnginePlatform *
    GetInstance()
    {
        GameEnginePlatform sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEnginePlatform();
    virtual ~GameEnginePlatform();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(GameEngineData *data, GameEngineSettingsSharedPtr settings);

private:
    void
    InitializePlatform(GameEngineData *data, GameEngineSettingsSharedPtr settings);

    void
    InitializeExceptPlatform();
};

}
