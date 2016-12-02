#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Function.h>

#include <algorithm>

using namespace std;

namespace FalconEngine
{


/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
ColorPalette Color::Palette = ColorPalette();

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Color::Color(uint32 hex) :
    R(hex),
    G(hex >> 8),
    B(hex >> 16),
    A(hex >> 24)
{
}

Color::Color(int r, int g, int b)
    : Color(r, g, b, 255)
{
}

Color::Color(int r, int g, int b, int a)
{
    typedef numeric_limits<uint8> uint8Limit;

    R = static_cast<uint8>(Clamp<int>(r, uint8Limit::min(), uint8Limit::max()));
    G = static_cast<uint8>(Clamp<int>(g, uint8Limit::min(), uint8Limit::max()));
    B = static_cast<uint8>(Clamp<int>(b, uint8Limit::min(), uint8Limit::max()));
    A = static_cast<uint8>(Clamp<int>(a, uint8Limit::min(), uint8Limit::max()));
}

Color::Color(float r, float g, float b, float a)
{
    typedef numeric_limits<uint8> uint8Limit;

    R = static_cast<uint8>(Clamp<float>(r * 255, uint8Limit::min(), uint8Limit::max()));
    G = static_cast<uint8>(Clamp<float>(g * 255, uint8Limit::min(), uint8Limit::max()));
    B = static_cast<uint8>(Clamp<float>(b * 255, uint8Limit::min(), uint8Limit::max()));
    A = static_cast<uint8>(Clamp<float>(a * 255, uint8Limit::min(), uint8Limit::max()));
}

Color::Color()
    : Color(0x000000)
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
Color::operator Vector3f() const
{
    return Vector3f(R / 255.0f, G / 255.0f, B / 255.0f);
}

Color::operator Vector4f() const
{
    return Vector4f(R / 255.0f, G / 255.0f, B / 255.0f, A / 255.0f);
}

bool operator==(Color lhs, Color rhs)
{
    return lhs.A == rhs.A &&
           lhs.R == rhs.R &&
           lhs.G == rhs.G &&
           lhs.B == rhs.B;
}

bool operator!=(Color lhs, Color rhs)
{
    return !(lhs == rhs);
}

}
