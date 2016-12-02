#pragma once

#include <cstdint>
#include <limits>
#include <type_traits>

namespace FalconEngine
{

typedef int8_t   int8;
typedef int16_t  int16;
typedef int32_t  int32;
typedef int64_t  int64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t  uint8;
typedef uint64_t uint64;

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type IntegerOdd(const T x)
{
    return x & 0x1;
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value, bool>::type IntegerEven(const T x)
{
    return (x % 2 == 0);
}

}
