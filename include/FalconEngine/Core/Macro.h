#pragma once

// SWITCH(Wuxiang): Uncommon this to use library as source code library.
// #define FALCON_ENGINE_INCLUDE_IMPLEMENTATION
#if defined(FALCON_ENGINE_INCLUDE_IMPLEMENTATION)
#include <FalconEngine/Core/MacroCodeLib.h>
#else
#include <FalconEngine/Core/MacroBinaryLib.h>
#endif