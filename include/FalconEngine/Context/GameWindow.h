#pragma once

namespace FalconEngine {

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
#if FALCON_ENGINE_PLATFOMR_QT
class GameWindow : public QOpenGLWidget, protected QOpenGLFunctions
#else
class GameWindow
#endif
{
public:
    GameWindow();
    ~GameWindow();

public:
};

}
