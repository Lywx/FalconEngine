#pragma once

// Prevents Windows headers from defining macros called min and max, which
// conflict with identifiers in the C++ standard library.
#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef far
#undef far
#endif
#ifdef near
#undef near
#endif
