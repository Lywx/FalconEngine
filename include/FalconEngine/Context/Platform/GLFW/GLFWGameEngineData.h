#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWInclude.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_CONTEXT GameEngineData final
{
public:
    GameEngineData();
    ~GameEngineData() = default;

public:
    GLFWwindow *mWindow;
};

}
