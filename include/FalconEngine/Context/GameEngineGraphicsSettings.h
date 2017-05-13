#pragma once

#include <FalconEngine/Context/Header.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineGraphicsSettings final
{
public:
    GameEngineGraphicsSettings();
    ~GameEngineGraphicsSettings() = default;

public:
    std::string mTitle;

    int         mWidth;
    int         mHeight;
};
#pragma warning(default: 4251)

using GameEngineGraphicsSettingsSharedPtr = std::shared_ptr<GameEngineGraphicsSettings>;

}
