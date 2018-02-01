#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <memory>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformRendererData final
{
public:
    explicit PlatformRendererData();
    ~PlatformRendererData();

public:
    void
    Initialize();

public:
    Microsoft::WRL::WeakRef mContext;
    Microsoft::WRL::WeakRef mDevice;
};
FALCON_ENGINE_CLASS_END

}
#endif
