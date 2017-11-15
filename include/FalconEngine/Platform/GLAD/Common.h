#pragma once

// NOTE(Wuxiang): Because GLAD will include <windows.h> which pollute the
// namespace, we need to avoid those Windows specific macro affect rest of the
// code base.
// https://stackoverflow.com/questions/4111899/is-there-an-easy-one-shot-solution-to-the-preprocessor-namespace-pollution-intro

// Prevents Windows headers from defining macros called min and max, which
// conflict with identifiers in the C++ standard library.
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Distinguishes between different types of handles so that we get better
// error checking at compile time.
#ifndef STRICT
#define STRICT
#endif

#include <glad/glad.h>

// NOTE(Wuxiang): We don't want these macros.
#ifdef far
#undef far
#endif
#ifdef near
#undef near
#endif
