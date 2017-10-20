#include <FalconEngine/Context/GameEngineWindow.h>
#include <FalconEngine/Context/GameEngineInput.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
#include <QtGui/QOpenGLContext.h>
namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineWindow::GameEngineWindow(QWidget *parent, Qt::WindowFlags flags) :
    QOpenGLWidget(parent, flags),
    mInput(nullptr),
    mSettings(nullptr)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineWindow::initializeGL()
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
GameEngineWindow::resizeEvent(QResizeEvent *event)
{
}

void
GameEngineWindow::resizeGL(int w, int h)
{
}

void
GameEngineWindow::paintGL()
{
}

void
GameEngineWindow::paintEvent(QPaintEvent *event)
{
}

void
GameEngineWindow::keyReleaseEvent(QKeyEvent *event)
{
    // TODO(Wuxiang): 2017-10-11 19:39
}

void
GameEngineWindow::keyPressEvent(QKeyEvent *event)
{
}

void
GameEngineWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void
GameEngineWindow::mouseMoveEvent(QMouseEvent *event)
{
}

void
GameEngineWindow::mousePressEvent(QMouseEvent *event)
{
}

void
GameEngineWindow::mouseReleaseEvent(QMouseEvent *event)
{
}

void
GameEngineWindow::wheelEvent(QWheelEvent *event)
{
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineWindow::InitializeInput()
{
}

}
#endif