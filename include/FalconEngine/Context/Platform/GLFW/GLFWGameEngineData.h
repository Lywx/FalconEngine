#pragma once

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
    GLFWwindow *mWindow;
};

}
