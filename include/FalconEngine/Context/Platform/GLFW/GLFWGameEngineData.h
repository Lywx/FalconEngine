#pragma once

#include <FalconEngine/Context/Platform/GLFW/GLFWHeader.h>

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
