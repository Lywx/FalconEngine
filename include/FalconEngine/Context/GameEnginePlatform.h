#pragma once

#include <FalconEngine/Context/Header.h>

#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

class GameEngineData;
using GameEngineDataSharedPtr = std::shared_ptr<GameEngineData>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEnginePlatform
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEnginePlatform *
    GetInstance()
    {
        static GameEnginePlatform sInstance;
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
    Initialize(GameEngineDataSharedPtr gameEngineData, GameEngineSettingsSharedPtr gameEngineSettings);

private:
    void
    InitializeData();

    void
    InitializePlatform(GameEngineDataSharedPtr gameEngineData);

private:
    GameEngineSettingsSharedPtr mGameEngineSettings;
};
#pragma warning(default: 4251)

}
