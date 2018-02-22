#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

class GameEngineData;
class GameEngineSettings;
class PlatformGameEngineWindow;

class PlatformGameEnginePlatformData;
FALCON_ENGINE_DELETER_DECLARE(PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter);

FALCON_ENGINE_CLASS_BEGIN GameEnginePlatform final
{
    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(GameEnginePlatform);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEnginePlatform();

public:
    ~GameEnginePlatform();

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
    InitializeDataPlatform();

    void
    InitializeLoaderPlatform();

    void
    InitializeWindowPlatform();

public:
    std::unique_ptr<PlatformGameEnginePlatformData, PlatformGameEnginePlatformDataDeleter> mData;

    // NEW(Wuxiang): May add multiple contexts and multiple windows support in the future.
    std::shared_ptr<PlatformGameEngineWindow>                                              mWindow;
};
FALCON_ENGINE_CLASS_END

}
