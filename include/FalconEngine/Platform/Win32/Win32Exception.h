#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
#include <Windows.h>

namespace FalconEngine
{
void
D3DCheckSuccess(HRESULT hr);
}

#endif