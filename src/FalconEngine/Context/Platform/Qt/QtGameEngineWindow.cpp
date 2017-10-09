#include <FalconEngine/Context/GameEngineWindow.h>

#if defined(FALCON_ENGINE_WINDOW_QT)
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
GameEngineWindow::keyReleaseEvent(QKeyEvent *event)
{
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
GameEngineWindow::InitializePlatform()
{
}

}
#endif