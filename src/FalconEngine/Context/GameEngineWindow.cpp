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
    InitializeData();
    InitializePlatform();
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEngineWindow::InitializeData()
{
    mInput = GameEngineInput::GetInstance();
    mSettings = GameEngineSettings::GetInstance();
}

}
