#pragma once

// NOTE(Wuxiang): Avoid extra header polluting the namespace.

#include <limits>
#include <type_traits>

#include <FalconEngine/Math/Constant.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

/************************************************************************/
/* Integer Function                                                     */
/************************************************************************/
template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
IsOdd(const T x)
{
    return x & 0x1;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
IsEven(const T x)
{
    return (x % 2 == 0);
}

/************************************************************************/
/* Math Function                                                        */
/************************************************************************/
template <typename T>
constexpr typename std::enable_if<std::is_signed<T>::value, T>::type
Abs(T a)
{
    return (a < 0) ? -a : a;
}

template <typename T>
constexpr typename std::enable_if<std::is_unsigned<T>::value, T>::type
Abs(T a)
{
    return a;
}

template <typename T>
typename std::enable_if < std::is_base_of<Vector2f, T>::value
|| std::is_base_of<Vector2i, T>::value
|| std::is_base_of<Vector3f, T>::value
|| std::is_base_of<Vector3i, T>::value
|| std::is_base_of<Vector4f, T>::value
|| std::is_base_of<Vector4i, T>::value, float >::type
Abs(const T& v)
{
    static_assert(std::is_base_of<Vector2f, T>::value
                  || std::is_base_of<Vector2i, T>::value
                  || std::is_base_of<Vector3f, T>::value
                  || std::is_base_of<Vector3i, T>::value
                  || std::is_base_of<Vector4f, T>::value
                  || std::is_base_of<Vector4i, T>::value, "Invalid type parameter.");

    return glm::distance<float, glm::highp>(v, T::Zero);
}

template <typename T>
T
Clamp(T value, T lower, T higher)
{
    value = value > higher ? higher : value;
    return value < lower ? lower : value;
}

template <typename T>
T
DegreeNormalize(T degree, T begin, T /* end */)
{
    degree = remainder(degree, T(360.0));

    if (degree < begin)
    {
        degree += 360.0;
    }

    return degree;
}

template <typename T>
constexpr typename std::enable_if<std::is_floating_point<T>::value, T>::type
Degree(T radian)
{
    return T(180.0 * radian / Pi);
}

template <typename T>
constexpr bool
Equal(T x, T y, float epsilon = Epsilon)
{
    return Abs(x - y) <= epsilon;
}

template <typename T>
constexpr bool
EqualAlmost(const T x, const T y, float epsilon = Epsilon)
{
    return Abs(x - y) <= epsilon;
}

template <typename T>
constexpr T
Lerp(T a, T b, T t)
{
    return a + t * (b - a);
}

template <typename T>
constexpr T
Max(T a, T b)
{
    return (a > b) ? a : b;
}

template <typename T>
constexpr T
Min(T a, T b)
{
    return (a < b) ? a : b;
}

template <typename T>
constexpr typename std::enable_if<std::is_floating_point<T>::value, T>::type
Radian(T degree)
{
    return T(Pi * degree / 180.0);
}

template <typename T>
constexpr T
Square(T x)
{
    return x * x;
}

template <typename T>
constexpr T
Smooth(T x)
{
    return x * x * (3 - 2 * x);
}

}
