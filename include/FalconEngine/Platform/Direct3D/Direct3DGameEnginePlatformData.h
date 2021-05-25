#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <memory>

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN PlatformGameEnginePlatformData final
{
public:
    explicit PlatformGameEnginePlatformData();
    ~PlatformGameEnginePlatformData();

public:
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> mContext;
    Microsoft::WRL::ComPtr<ID3D11Device1>        mDevice;
    D3D_FEATURE_LEVEL                            mFeatureLevel;

public:
};
FALCON_ENGINE_CLASS_END

}
#endif
