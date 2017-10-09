#pragma once

#include <FalconEngine/Context/Common.h>
#include <FalconEngine/Context/GameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/Common.h>
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
    GameEngineWindow mWindow;
};

}
#endif