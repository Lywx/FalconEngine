// NOTE(Wuxiang): There Have to be no include guard.

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)
// Prevents Windows headers from defining macros called min and max, which
// conflict with identifiers in the C++ standard library.
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef NODRAWTEXT
#define NODRAWTEXT
#endif

#ifndef NOGDI
#define NOGDI
#endif

#ifndef NOBITMAP
#define NOBITMAP
#endif

// Include <mcx.h> if you need this
#ifndef NOMCX
#define NOMCX
#endif

// Include <winsvc.h> if you need this
#ifndef NOSERVICE
#define NOSERVICE
#endif

// WinHelp is deprecated
#ifndef NOHELP
#define NOHELP
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#endif
