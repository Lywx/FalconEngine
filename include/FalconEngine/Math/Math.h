#pragma once

namespace FalconEngine {

/************************************************************************/
/* Constants                                                            */
/************************************************************************/
constexpr float Pi      = 3.1415926535897932384626433832795f;
constexpr float TwoPi   = Pi * 2.0f;
constexpr float PiOver2 = Pi / 2.0f;
constexpr float PiOver4 = Pi / 4.0f;
constexpr float E       = 2.71828182846f;
constexpr float Epsilon = 1.0e-10f;

/************************************************************************/
/* Math Functions                                                       */
/************************************************************************/
template <typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, T>::type Abs(T a)
{
    return (a < 0) ? -a : a;
}

template <typename T>
constexpr typename std::enable_if<std::is_unsigned<T>::value, T>::type Abs(T a)
{
    return a;
}

template <typename T>
constexpr T Square(T x) { return x * x; }

template <typename T>
constexpr T Min(T a, T b) { return (a < b) ? a : b; }

template <typename T>
constexpr T Max(T a, T b) { return (a > b) ? a : b; }

template <typename T>
constexpr void Clamp(T& value, const T low, const T high) { (value < low) ? (value = low) : (value > high) ? (value = high) : (value); }

template <typename T>
T Lerp(const T a, const T b, T t) { return a + t * (b - a); }

template <typename T>
T Smooth(const T x) { return x * x * (3 - 2 * x); }

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type IsOdd(T x)
{
    return x & 0x1;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type IsEven(T x)
{
    return (x % 2 == 0);
}

inline constexpr bool IsEqual(float x, float y, float epsilon = Epsilon)
{
    return Abs(x - y) <= epsilon;
}

inline constexpr bool IsWithin(float x, float epsilon = Epsilon)
{
    return Abs(x - epsilon) <= epsilon;
}

}
