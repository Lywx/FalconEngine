#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>

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
    bool mRunning;
};
FALCON_ENGINE_CLASS_END

}
