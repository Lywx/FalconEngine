#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Core/GameEngineSettings.h>
#include <FalconEngine/Platform/Qt/Common.h>
#include <QtWidgets/QOpenGLWidget>

namespace FalconEngine
{

class GameEngineInput;

// @summary Game window represent the window system encapsulation. You would use
// same GameWindow class for different window system like, GLFW, Qt etc.
class FALCON_ENGINE_API GameEngineWindow : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GameEngineWindow(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
public:
    ~GameEngineWindow() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    void
    InitializeInputPlatform();

public:
    virtual void
    initializeGL() override;

    virtual void
    resizeEvent(QResizeEvent *event) override;

    virtual void
    resizeGL(int w, int h) override;

    virtual void
    paintGL() override;

    virtual void
    paintEvent(QPaintEvent *event) override;

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

private:
    GameEngineInput    *mInput;
    GameEngineSettings *mSettings;
};

}
#endif
