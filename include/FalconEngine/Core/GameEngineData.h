#pragma once

#include <memory>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN GameEngineData final
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    FALCON_ENGINE_SINGLETON_LEAK_DECLARE(GameEngineData);

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
