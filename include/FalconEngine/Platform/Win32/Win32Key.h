#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Platform/Win32/Common.h>

namespace FalconEngine
{

// @remark The enum value is copied from the GLFW definition to smooth the conversion.
enum class Key
{
    Unknown = 0,

    D0 = 48,
    D1 = 49,
    D2 = 50,
    D3 = 51,
    D4 = 52,
    D5 = 53,
    D6 = 54,
    D7 = 55,
    D8 = 56,
    D9 = 57,

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    Escape = VK_ESCAPE,
    Space = VK_SPACE,
};

}

#endif