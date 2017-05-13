#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWHeader.h>

namespace FalconEngine
{

class FALCON_ENGINE_API GameEngineData final
{
public:
    GameEngineData();
    ~GameEngineData() = default;

public:
    GLFWwindow *mWindow;
};

}
