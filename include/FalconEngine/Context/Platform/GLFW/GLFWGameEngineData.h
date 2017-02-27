#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWInclude.h>

namespace FalconEngine
{

class GameEngineData sealed
{
public:
    GameEngineData();
    ~GameEngineData() = default;

public:
    GLFWwindow *mWindow;
};

}
