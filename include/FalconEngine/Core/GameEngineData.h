#pragma once

#include <FalconEngine/Core/Common.h>
#include <FalconEngine/Core/GameEngineWindow.h>

namespace FalconEngine
{

class FALCON_ENGINE_API GameEngineData final
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
    // NEW(Wuxiang): May add multiple contexts and multiple windows support in the future.
    std::shared_ptr<GameEngineWindow> mWindow;
};

}