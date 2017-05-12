#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Function.h>

#include <algorithm>

using namespace std;

namespace FalconEngine
{


/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const Color ColorPalette::TransparentBlack(Color(0));
const Color ColorPalette::Transparent(Color(0));
const Color ColorPalette::AliceBlue(Color(0xfffff8f0));
const Color ColorPalette::AntiqueWhite(Color(0xffd7ebfa));
const Color ColorPalette::Aqua(Color(0xffffff00));
const Color ColorPalette::Aquamarine(Color(0xffd4ff7f));
const Color ColorPalette::Azure(Color(0xfffffff0));
const Color ColorPalette::Beige(Color(0xffdcf5f5));
const Color ColorPalette::Bisque(Color(0xffc4e4ff));
const Color ColorPalette::Black(Color(0xff000000));
const Color ColorPalette::BlanchedAlmond(Color(0xffcdebff));
const Color ColorPalette::Blue(Color(0xffff0000));
const Color ColorPalette::BlueViolet(Color(0xffe22b8a));
const Color ColorPalette::Brown(Color(0xff2a2aa5));
const Color ColorPalette::BurlyWood(Color(0xff87b8de));
const Color ColorPalette::CadetBlue(Color(0xffa09e5f));
const Color ColorPalette::Chartreuse(Color(0xff00ff7f));
const Color ColorPalette::Chocolate(Color(0xff1e69d2));
const Color ColorPalette::Coral(Color(0xff507fff));
const Color ColorPalette::CornflowerBlue(Color(0xffed9564));
const Color ColorPalette::Cornsilk(Color(0xffdcf8ff));
const Color ColorPalette::Crimson(Color(0xff3c14dc));
const Color ColorPalette::Cyan(Color(0xffffff00));
const Color ColorPalette::DarkBlue(Color(0xff8b0000));
const Color ColorPalette::DarkCyan(Color(0xff8b8b00));
const Color ColorPalette::DarkGoldenrod(Color(0xff0b86b8));
const Color ColorPalette::DarkGray(Color(0xffa9a9a9));
const Color ColorPalette::DarkGreen(Color(0xff006400));
const Color ColorPalette::DarkKhaki(Color(0xff6bb7bd));
const Color ColorPalette::DarkMagenta(Color(0xff8b008b));
const Color ColorPalette::DarkOliveGreen(Color(0xff2f6b55));
const Color ColorPalette::DarkOrange(Color(0xff008cff));
const Color ColorPalette::DarkOrchid(Color(0xffcc3299));
const Color ColorPalette::DarkRed(Color(0xff00008b));
const Color ColorPalette::DarkSalmon(Color(0xff7a96e9));
const Color ColorPalette::DarkSeaGreen(Color(0xff8bbc8f));
const Color ColorPalette::DarkSlateBlue(Color(0xff8b3d48));
const Color ColorPalette::DarkSlateGray(Color(0xff4f4f2f));
const Color ColorPalette::DarkTurquoise(Color(0xffd1ce00));
const Color ColorPalette::DarkViolet(Color(0xffd30094));
const Color ColorPalette::DeepPink(Color(0xff9314ff));
const Color ColorPalette::DeepSkyBlue(Color(0xffffbf00));
const Color ColorPalette::DimGray(Color(0xff696969));
const Color ColorPalette::DodgerBlue(Color(0xffff901e));
const Color ColorPalette::Firebrick(Color(0xff2222b2));
const Color ColorPalette::FloralWhite(Color(0xfff0faff));
const Color ColorPalette::ForestGreen(Color(0xff228b22));
const Color ColorPalette::Fuchsia(Color(0xffff00ff));
const Color ColorPalette::Gainsboro(Color(0xffdcdcdc));
const Color ColorPalette::GhostWhite(Color(0xfffff8f8));
const Color ColorPalette::Gold(Color(0xff00d7ff));
const Color ColorPalette::Goldenrod(Color(0xff20a5da));
const Color ColorPalette::Gray(Color(0xff808080));
const Color ColorPalette::Green(Color(0xff008000));
const Color ColorPalette::GreenYellow(Color(0xff2fffad));
const Color ColorPalette::Honeydew(Color(0xfff0fff0));
const Color ColorPalette::HotPink(Color(0xffb469ff));
const Color ColorPalette::IndianRed(Color(0xff5c5ccd));
const Color ColorPalette::Indigo(Color(0xff82004b));
const Color ColorPalette::Ivory(Color(0xfff0ffff));
const Color ColorPalette::Khaki(Color(0xff8ce6f0));
const Color ColorPalette::Lavender(Color(0xfffae6e6));
const Color ColorPalette::LavenderBlush(Color(0xfff5f0ff));
const Color ColorPalette::LawnGreen(Color(0xff00fc7c));
const Color ColorPalette::LemonChiffon(Color(0xffcdfaff));
const Color ColorPalette::LightBlue(Color(0xffe6d8ad));
const Color ColorPalette::LightCoral(Color(0xff8080f0));
const Color ColorPalette::LightCyan(Color(0xffffffe0));
const Color ColorPalette::LightGoldenrodYellow(Color(0xffd2fafa));
const Color ColorPalette::LightGray(Color(0xffd3d3d3));
const Color ColorPalette::LightGreen(Color(0xff90ee90));
const Color ColorPalette::LightPink(Color(0xffc1b6ff));
const Color ColorPalette::LightSalmon(Color(0xff7aa0ff));
const Color ColorPalette::LightSeaGreen(Color(0xffaab220));
const Color ColorPalette::LightSkyBlue(Color(0xffface87));
const Color ColorPalette::LightSlateGray(Color(0xff998877));
const Color ColorPalette::LightSteelBlue(Color(0xffdec4b0));
const Color ColorPalette::LightYellow(Color(0xffe0ffff));
const Color ColorPalette::Lime(Color(0xff00ff00));
const Color ColorPalette::LimeGreen(Color(0xff32cd32));
const Color ColorPalette::Linen(Color(0xffe6f0fa));
const Color ColorPalette::Magenta(Color(0xffff00ff));
const Color ColorPalette::Maroon(Color(0xff000080));
const Color ColorPalette::MediumAquamarine(Color(0xffaacd66));
const Color ColorPalette::MediumBlue(Color(0xffcd0000));
const Color ColorPalette::MediumOrchid(Color(0xffd355ba));
const Color ColorPalette::MediumPurple(Color(0xffdb7093));
const Color ColorPalette::MediumSeaGreen(Color(0xff71b33c));
const Color ColorPalette::MediumSlateBlue(Color(0xffee687b));
const Color ColorPalette::MediumSpringGreen(Color(0xff9afa00));
const Color ColorPalette::MediumTurquoise(Color(0xffccd148));
const Color ColorPalette::MediumVioletRed(Color(0xff8515c7));
const Color ColorPalette::MidnightBlue(Color(0xff701919));
const Color ColorPalette::MintCream(Color(0xfffafff5));
const Color ColorPalette::MistyRose(Color(0xffe1e4ff));
const Color ColorPalette::Moccasin(Color(0xffb5e4ff));
const Color ColorPalette::MonoGameOrange(Color(0xff003ce7));
const Color ColorPalette::NavajoWhite(Color(0xffaddeff));
const Color ColorPalette::Navy(Color(0xff800000));
const Color ColorPalette::OldLace(Color(0xffe6f5fd));
const Color ColorPalette::Olive(Color(0xff008080));
const Color ColorPalette::OliveDrab(Color(0xff238e6b));
const Color ColorPalette::Orange(Color(0xff00a5ff));
const Color ColorPalette::OrangeRed(Color(0xff0045ff));
const Color ColorPalette::Orchid(Color(0xffd670da));
const Color ColorPalette::PaleGoldenrod(Color(0xffaae8ee));
const Color ColorPalette::PaleGreen(Color(0xff98fb98));
const Color ColorPalette::PaleTurquoise(Color(0xffeeeeaf));
const Color ColorPalette::PaleVioletRed(Color(0xff9370db));
const Color ColorPalette::PapayaWhip(Color(0xffd5efff));
const Color ColorPalette::PeachPuff(Color(0xffb9daff));
const Color ColorPalette::Peru(Color(0xff3f85cd));
const Color ColorPalette::Pink(Color(0xffcbc0ff));
const Color ColorPalette::Plum(Color(0xffdda0dd));
const Color ColorPalette::PowderBlue(Color(0xffe6e0b0));
const Color ColorPalette::Purple(Color(0xff800080));
const Color ColorPalette::Red(Color(0xff0000ff));
const Color ColorPalette::RosyBrown(Color(0xff8f8fbc));
const Color ColorPalette::RoyalBlue(Color(0xffe16941));
const Color ColorPalette::SaddleBrown(Color(0xff13458b));
const Color ColorPalette::Salmon(Color(0xff7280fa));
const Color ColorPalette::SandyBrown(Color(0xff60a4f4));
const Color ColorPalette::SeaGreen(Color(0xff578b2e));
const Color ColorPalette::SeaShell(Color(0xffeef5ff));
const Color ColorPalette::Sienna(Color(0xff2d52a0));
const Color ColorPalette::Silver(Color(0xffc0c0c0));
const Color ColorPalette::SkyBlue(Color(0xffebce87));
const Color ColorPalette::SlateBlue(Color(0xffcd5a6a));
const Color ColorPalette::SlateGray(Color(0xff908070));
const Color ColorPalette::Snow(Color(0xfffafaff));
const Color ColorPalette::SpringGreen(Color(0xff7fff00));
const Color ColorPalette::SteelBlue(Color(0xffb48246));
const Color ColorPalette::Tan(Color(0xff8cb4d2));
const Color ColorPalette::Teal(Color(0xff808000));
const Color ColorPalette::Thistle(Color(0xffd8bfd8));
const Color ColorPalette::Tomato(Color(0xff4763ff));
const Color ColorPalette::Turquoise(Color(0xffd0e040));
const Color ColorPalette::Violet(Color(0xffee82ee));
const Color ColorPalette::Wheat(Color(0xffb3def5));
const Color ColorPalette::White(Color(UINT32_MAX));
const Color ColorPalette::WhiteSmoke(Color(0xfff5f5f5));
const Color ColorPalette::Yellow(Color(0xff00ffff));
const Color ColorPalette::YellowGreen(Color(0xff32cd9a));

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Color::Color(uint32 hex) :
    R(uint8(hex)),
    G(uint8(hex >> 8)),
    B(uint8(hex >> 16)),
    A(uint8(hex >> 24))
{
}

Color::Color(int r, int g, int b) :
    Color(r, g, b, 255)
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

Color::Color(float r, float g, float b) :
    Color(r, g, b, 1.0f)
{
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

Color
Transparent(Color color, uint8 a)
{
    color.A = a;
    return color;
}

Color
Transparent(Color color, float a)
{
    typedef numeric_limits<uint8> uint8Limit;

    color.A = static_cast<uint8>(Clamp<float>(a * 255, uint8Limit::min(), uint8Limit::max()));
    return color;
}

}
