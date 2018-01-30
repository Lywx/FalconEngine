#include <FalconEngine/Core/GameEngineWindow.h>
#include <FalconEngine/Core/GameEngineInput.h>
#include <FalconEngine/Core/GameEngineSettings.h>

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
