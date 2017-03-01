#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineInputSettings.h>

namespace FalconEngine
{

GameEngineSettings::GameEngineSettings()
{
    mGraphics = std::make_shared<GameEngineGraphicsSettings>();
    mInput = std::make_shared<GameEngineInputSettings>();
}

}
