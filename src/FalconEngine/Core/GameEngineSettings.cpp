#include <FalconEngine/Core/GameEngineSettings.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineSettings::GameEngineSettings() :
    mFrameElapsedMillisecond(16.66666666666),
    mMouseLimited(true),
    mMouseVisible(false),
    mWindowVisible(true),
    mWindowTitle("Falcon Engine Game"),
    mWindowWidth(800),
    mWindowHeight(600),
    mWindowNear(0.0f),
    mWindowFar(1.0f),
    mOpenGLErrorBreak(false)
{
}
}
