#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)
#include <FalconEngine/Platform/Direct3D/Direct3DLib.h>

namespace FalconEngine
{

void
Direct3DDebugInitialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device);

}

#endif