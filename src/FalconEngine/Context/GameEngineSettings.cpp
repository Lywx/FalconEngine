#include <FalconEngine/Context/GameEngineSettings.h>

namespace FalconEngine
{

GameEngineSettings::GameEngineSettings()
{
    mGraphics = std::make_shared<GameEngineGraphicsSettings>();
    mInput = std::make_shared<GameEngineInputSettings>();
}

}
