#pragma once

#include <FalconEngine/Core/Common.h>

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
private:
    GameEnginePlatform();

public:
    virtual ~GameEnginePlatform();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

private:
    void
    InitializeData();

    void
    InitializePlatform();

    void
    InitializeContextPlatform();

    void
    InitializeLoaderPlatform();

    void
    InitializeWindowPlatform();
};
#pragma warning(default: 4251)

}
