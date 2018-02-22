#include <FalconEngine/Core/GameEnginePlatform.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEnginePlatform::GameEnginePlatform()
{
}

GameEnginePlatform::~GameEnginePlatform()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEnginePlatform::Destroy()
{
    mData.reset();
    mWindow.reset();
}

void
GameEnginePlatform::Initialize()
{
    InitializeData();
    InitializePlatform();
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
void
GameEnginePlatform::InitializeData()
{
}

}
