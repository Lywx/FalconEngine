#include <FalconEngine/Core/GameEngineWindow.h>
#include <FalconEngine/Core/GameEngineData.h>
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
    InitializeData();
    InitializePlatform();
}

void
GameEngineWindow::InitializeData()
{
    mData = GameEngineData::GetInstance();
    mInput = GameEngineInput::GetInstance();
    mSettings = GameEngineSettings::GetInstance();
}

}
