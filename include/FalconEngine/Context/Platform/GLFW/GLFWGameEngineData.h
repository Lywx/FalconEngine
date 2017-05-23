#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWHeader.h>

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

public:
    GameEngineData();
    ~GameEngineData() = default;

public:
    GLFWwindow *mWindow;
};

}
