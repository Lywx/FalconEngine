#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <memory>

namespace FalconEngine
{

class PlatformGameEngineWindow;
FALCON_ENGINE_CLASS_BEGIN PlatformGameEnginePlatformData final
{
public:
    explicit PlatformGameEnginePlatformData();
    ~PlatformGameEnginePlatformData();
};
FALCON_ENGINE_CLASS_END

}
#endif
