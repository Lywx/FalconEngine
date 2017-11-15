#pragma once

#include <FalconEngine/Core/Common.h>

#include <FalconEngine/Core/Platform/GLFW/Common.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/Common.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformWindowData final
{
public:
    explicit PlatformWindowData(GLFWwindow *handle);
    ~PlatformWindowData() = default;

public:
    GLFWwindow *mHandle;
};
#pragma warning(default: 4251)

}
