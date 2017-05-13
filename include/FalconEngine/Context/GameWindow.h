#pragma once

#include <FalconEngine/Context/Header.h>

namespace FalconEngine
{

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
#if defined(FALCON_ENGINE_PLATFORM_QT)
class FALCON_ENGINE_API GameWindow : public QOpenGLWidget, protected QOpenGLFunctions
#else
class FALCON_ENGINE_API GameWindow
#endif
{
public:
    GameWindow();
    ~GameWindow();

public:
};

}
