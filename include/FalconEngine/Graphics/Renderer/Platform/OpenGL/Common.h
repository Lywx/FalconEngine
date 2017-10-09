#pragma once

#include <FalconEngine/Graphics/Common.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/Common.h>
#else defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Context/Platform/Qt/Common.h>
#endif
