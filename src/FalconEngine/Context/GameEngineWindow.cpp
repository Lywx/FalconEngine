#include <FalconEngine/Context/GameEngineWindow.h>

#include <FalconEngine/Context/GameEngineInput.h>

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineWindow::Initialize()
{
    mInput = GameEngineInput::GetInstance();
    mSettings = GameEngineSettings::GetInstance();

    InitializeInputPlatform();
}

}
