#pragma once

#include <type_traits>

#include <FalconEngine/Math/Constant.h>

namespace FalconEngine
{

template <typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, T>::type Abs(const T a)
{
    return (a < 0) ? -a : a;
}

template <typename T>
constexpr typename std::enable_if<std::is_unsigned<T>::value, T>::type Abs(const T a)
{
    return a;
}

template <typename T>
constexpr T Square(const T x)
{
    return x * x;
}

template <typename T>
constexpr T Min(T a, T b)
{
    return (a < b) ? a : b;
}

template <typename T>
constexpr T Max(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
constexpr T Clamp(T value, const T lower, const T higher)
{
    value = value > higher ? higher : value;
    return value < lower ? lower : value;
}

template <typename T>
constexpr T Lerp(const T a, const T b, const T t)
{
    return a + t * (b - a);
}

template <typename T>
T Smooth(const T x)
{
    return x * x * (3 - 2 * x);
}

template <typename T>
constexpr bool Equal(const T x, const T y, float epsilon = Epsilon)
{
    return Abs(x - y) <= epsilon;
}

template <typename T>
constexpr bool EqualAlmost(const T x, const T y, float epsilon = Epsilon)
{
    return Abs(x - y) <= epsilon;
}

}
