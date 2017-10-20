#pragma once

#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/Common.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API PlatformWindowData final
{
public:
    explicit PlatformWindowData(QtWindow *window);
    ~PlatformWindowData();

public:
    GLFWwindow                            *mWindow;
};
#pragma warning(default: 4251)

}
