#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWInclude.h>

namespace FalconEngine
{

class GameEngineData final
{
public:
    GameEngineData();
    ~GameEngineData() = default;

public:
    GLFWwindow *mWindow;
};

}
