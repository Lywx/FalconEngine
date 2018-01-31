#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/GameEngineWindow.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN GameEngineData final
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEngineData *
    GetInstance()
    {
        static GameEngineData sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineData();

public:
    ~GameEngineData() = default;

public:
    bool                              mRunning;

    // NEW(Wuxiang): May add multiple contexts and multiple windows support in the future.
    std::shared_ptr<GameEngineWindow> mWindow;
};
FALCON_ENGINE_CLASS_END

}
