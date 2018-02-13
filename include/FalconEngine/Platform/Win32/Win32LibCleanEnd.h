// NOTE(Wuxiang): There Have to be no include guard.

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)

#ifdef far
#undef far
#endif
#ifdef near
#undef near
#endif

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#endif