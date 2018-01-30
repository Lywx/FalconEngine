#pragma once

#include <FalconEngine/Core/Common.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/Common.h>
#elif defined(FALCON_ENGINE_API_DIRECTX)
#include <FalconEngine/Platform/DirectX/Common.h>
#else
#endif