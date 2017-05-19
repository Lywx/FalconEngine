#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineInputSettings.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineSettings::GameEngineSettings()
{
    mGraphics = std::make_shared<GameEngineGraphicsSettings>(800, 600);
    mInput = std::make_shared<GameEngineInputSettings>();
}

}
