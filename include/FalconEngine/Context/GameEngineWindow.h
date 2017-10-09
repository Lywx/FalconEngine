#pragma once

#include <FalconEngine/Context/Common.h>

#include <FalconEngine/Context/GameEngineSettings.h>
#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/Common.h>
#elif defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Context/Platform/Qt/Common.h>
#include <QtWidgets/QOpenGLWidget>
#endif

namespace FalconEngine
{

class GameEngineInput;

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
#if defined(FALCON_ENGINE_WINDOW_GLFW)
class FALCON_ENGINE_API GameEngineWindow
#elif defined(FALCON_ENGINE_WINDOW_QT)
class FALCON_ENGINE_API GameEngineWindow : public QOpenGLWidget
#endif
{
public:
#if defined(FALCON_ENGINE_WINDOW_GLFW)
    explicit GameEngineWindow(GLFWwindow *window);
#elif defined(FALCON_ENGINE_WINDOW_QT)
    explicit GameEngineWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
#endif
    ~GameEngineWindow() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

public:
#if defined(FALCON_ENGINE_WINDOW_GLFW)
    void
    KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void
    MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

    void
    MousePositionCallback(GLFWwindow *window, double x, double y);

    void
    ScrollCallback(GLFWwindow *window, double x, double y);
#endif
#if defined(FALCON_ENGINE_WINDOW_QT)
    virtual void
    keyReleaseEvent(QKeyEvent *event) override;

    virtual void
    keyPressEvent(QKeyEvent *event) override;

    virtual void
    mouseDoubleClickEvent(QMouseEvent *event) override;

    virtual void
    mouseMoveEvent(QMouseEvent *event) override;

    virtual void
    mousePressEvent(QMouseEvent *event) override;

    virtual void
    mouseReleaseEvent(QMouseEvent *event) override;

    virtual void
    wheelEvent(QWheelEvent *event) override;
#endif

    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
private:
    void
    InitializeData();

    void
    InitializePlatform();

private:
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};

}