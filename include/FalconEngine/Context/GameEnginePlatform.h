#pragma once

#include <FalconEngine/Context/Header.h>

#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;

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
    Initialize(GameEngineData *gameEngineData, GameEngineSettings *gameEngineSettings);

private:
    void
    InitializeData();

    void
    InitializePlatform(GameEngineData *gameEngineData);

private:
    GameEngineSettings *mGameEngineSettings;
};
#pragma warning(default: 4251)

}
