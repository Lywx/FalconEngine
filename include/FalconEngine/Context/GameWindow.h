#pragma once

#include <FalconEngine/Context/Common.h>

namespace FalconEngine
{

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
#if defined(FALCON_ENGINE_WINDOW_QT)
class FALCON_ENGINE_API GameWindow : public QOpenGLWidget, protected QOpenGLFunctions
#elif defined(FALCON_ENGINE_WINDOW_GLFW)
class FALCON_ENGINE_API GameWindow
#endif
{
public:
    GameWindow();
    ~GameWindow();

public:
};

}
