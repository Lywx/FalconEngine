#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Platform/GLFW/GLFWGameEngineWindow.h>
#elif defined(FALCON_ENGINE_WINDOW_QT)
#include <FalconEngine/Platform/Qt/QtGameEngineWindow.h>
#elif defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Platform/Win32/Win32GameEngineWindow.h>
#endif