#include <FalconEngine/Platform/Qt/QtGameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Core/GameEngineInput.h>
#include <QtGui/QOpenGLContext.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformGameEngineWindow::PlatformGameEngineWindow(QWidget *parent, Qt::WindowFlags flags) :
    QOpenGLWidget(parent, flags),
    mInput(nullptr),
    mSettings(nullptr)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformGameEngineWindow::initializeGL()
{
    QSurfaceFormat format;
    format.setOption(QSurfaceFormat::DebugContext);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    format.setSwapInterval(1);
    format.setVersion(4, 3);

    setFormat(format);
}

void
PlatformGameEngineWindow::resizeEvent(QResizeEvent *event)
{
}

void
PlatformGameEngineWindow::resizeGL(int w, int h)
{
}

void
PlatformGameEngineWindow::paintGL()
{
}

void
PlatformGameEngineWindow::paintEvent(QPaintEvent *event)
{
}

void
PlatformGameEngineWindow::keyReleaseEvent(QKeyEvent *event)
{
    // TODO(Wuxiang): 2017-10-11 19:39
}

void
PlatformGameEngineWindow::keyPressEvent(QKeyEvent *event)
{
}

void
PlatformGameEngineWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void
PlatformGameEngineWindow::mouseMoveEvent(QMouseEvent *event)
{
}

void
PlatformGameEngineWindow::mousePressEvent(QMouseEvent *event)
{
}

void
PlatformGameEngineWindow::mouseReleaseEvent(QMouseEvent *event)
{
}

void
PlatformGameEngineWindow::wheelEvent(QWheelEvent *event)
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
PlatformGameEngineWindow::InitializeInput()
{
}

}
#endif