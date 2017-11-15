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
