#pragma once

#include <cstdint>
#include <limits>

#include <FalconEngine/Math/Integer.h>
#include <FalconEngine/Math/Vector3f.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine
{

class ColorPalette;
class Color
{
public:
    static ColorPalette Palette;

    explicit Color(uint32 hex);
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(float r, float g, float b, float a);
    Color();

    operator Vector3f() const;
    operator Vector4f() const;

    uint8 R;
    uint8 G;
    uint8 B;
    uint8 A;
};

bool operator==(Color lhs, Color rhs);
bool operator!=(Color lhs, Color rhs);

class ColorPalette
{
public:
    const Color TransparentBlack;

    /// <summary>
    /// Transparent color (R:0,G:0,B:0,A:0).
    /// </summary>
    const Color Transparent;

    /// <summary>
    /// AliceBlue color (R:240,G:248,B:255,A:255).
    /// </summary>
    const Color AliceBlue;

    /// <summary>
    /// AntiqueWhite color (R:250,G:235,B:215,A:255).
    /// </summary>
    const Color AntiqueWhite;

    /// <summary>
    /// Aqua color (R:0,G:255,B:255,A:255).
    /// </summary>
    const Color Aqua;

    /// <summary>
    /// Aquamarine color (R:127,G:255,B:212,A:255).
    /// </summary>
    const Color Aquamarine;

    /// <summary>
    /// Azure color (R:240,G:255,B:255,A:255).
    /// </summary>
    const Color Azure;

    /// <summary>
    /// Beige color (R:245,G:245,B:220,A:255).
    /// </summary>
    const Color Beige;

    /// <summary>
    /// Bisque color (R:255,G:228,B:196,A:255).
    /// </summary>
    const Color Bisque;

    /// <summary>
    /// Black color (R:0,G:0,B:0,A:255).
    /// </summary>
    const Color Black;

    /// <summary>
    /// BlanchedAlmond color (R:255,G:235,B:205,A:255).
    /// </summary>
    const Color BlanchedAlmond;

    /// <summary>
    /// Blue color (R:0,G:0,B:255,A:255).
    /// </summary>
    const Color Blue;

    /// <summary>
    /// BlueViolet color (R:138,G:43,B:226,A:255).
    /// </summary>
    const Color BlueViolet;

    /// <summary>
    /// Brown color (R:165,G:42,B:42,A:255).
    /// </summary>
    const Color Brown;

    /// <summary>
    /// BurlyWood color (R:222,G:184,B:135,A:255).
    /// </summary>
    const Color BurlyWood;

    /// <summary>
    /// CadetBlue color (R:95,G:158,B:160,A:255).
    /// </summary>
    const Color CadetBlue;

    /// <summary>
    /// Chartreuse color (R:127,G:255,B:0,A:255).
    /// </summary>
    const Color Chartreuse;

    /// <summary>
    /// Chocolate color (R:210,G:105,B:30,A:255).
    /// </summary>
    const Color Chocolate;

    /// <summary>
    /// Coral color (R:255,G:127,B:80,A:255).
    /// </summary>
    const Color Coral;

    /// <summary>
    /// CornflowerBlue color (R:100,G:149,B:237,A:255).
    /// </summary>
    const Color CornflowerBlue;

    /// <summary>
    /// Cornsilk color (R:255,G:248,B:220,A:255).
    /// </summary>
    const Color Cornsilk;

    /// <summary>
    /// Crimson color (R:220,G:20,B:60,A:255).
    /// </summary>
    const Color Crimson;

    /// <summary>
    /// Cyan color (R:0,G:255,B:255,A:255).
    /// </summary>
    const Color Cyan;

    /// <summary>
    /// DarkBlue color (R:0,G:0,B:139,A:255).
    /// </summary>
    const Color DarkBlue;

    /// <summary>
    /// DarkCyan color (R:0,G:139,B:139,A:255).
    /// </summary>
    const Color DarkCyan;

    /// <summary>
    /// DarkGoldenrod color (R:184,G:134,B:11,A:255).
    /// </summary>
    const Color DarkGoldenrod;

    /// <summary>
    /// DarkGray color (R:169,G:169,B:169,A:255).
    /// </summary>
    const Color DarkGray;

    /// <summary>
    /// DarkGreen color (R:0,G:100,B:0,A:255).
    /// </summary>
    const Color DarkGreen;

    /// <summary>
    /// DarkKhaki color (R:189,G:183,B:107,A:255).
    /// </summary>
    const Color DarkKhaki;

    /// <summary>
    /// DarkMagenta color (R:139,G:0,B:139,A:255).
    /// </summary>
    const Color DarkMagenta;

    /// <summary>
    /// DarkOliveGreen color (R:85,G:107,B:47,A:255).
    /// </summary>
    const Color DarkOliveGreen;

    /// <summary>
    /// DarkOrange color (R:255,G:140,B:0,A:255).
    /// </summary>
    const Color DarkOrange;

    /// <summary>
    /// DarkOrchid color (R:153,G:50,B:204,A:255).
    /// </summary>
    const Color DarkOrchid;

    /// <summary>
    /// DarkRed color (R:139,G:0,B:0,A:255).
    /// </summary>
    const Color DarkRed;

    /// <summary>
    /// DarkSalmon color (R:233,G:150,B:122,A:255).
    /// </summary>
    const Color DarkSalmon;

    /// <summary>
    /// DarkSeaGreen color (R:143,G:188,B:139,A:255).
    /// </summary>
    const Color DarkSeaGreen;

    /// <summary>
    /// DarkSlateBlue color (R:72,G:61,B:139,A:255).
    /// </summary>
    const Color DarkSlateBlue;

    /// <summary>
    /// DarkSlateGray color (R:47,G:79,B:79,A:255).
    /// </summary>
    const Color DarkSlateGray;

    /// <summary>
    /// DarkTurquoise color (R:0,G:206,B:209,A:255).
    /// </summary>
    const Color DarkTurquoise;

    /// <summary>
    /// DarkViolet color (R:148,G:0,B:211,A:255).
    /// </summary>
    const Color DarkViolet;

    /// <summary>
    /// DeepPink color (R:255,G:20,B:147,A:255).
    /// </summary>
    const Color DeepPink;

    /// <summary>
    /// DeepSkyBlue color (R:0,G:191,B:255,A:255).
    /// </summary>
    const Color DeepSkyBlue;

    /// <summary>
    /// DimGray color (R:105,G:105,B:105,A:255).
    /// </summary>
    const Color DimGray;

    /// <summary>
    /// DodgerBlue color (R:30,G:144,B:255,A:255).
    /// </summary>
    const Color DodgerBlue;

    /// <summary>
    /// Firebrick color (R:178,G:34,B:34,A:255).
    /// </summary>
    const Color Firebrick;

    /// <summary>
    /// FloralWhite color (R:255,G:250,B:240,A:255).
    /// </summary>
    const Color FloralWhite;

    /// <summary>
    /// ForestGreen color (R:34,G:139,B:34,A:255).
    /// </summary>
    const Color ForestGreen;

    /// <summary>
    /// Fuchsia color (R:255,G:0,B:255,A:255).
    /// </summary>
    const Color Fuchsia;

    /// <summary>
    /// Gainsboro color (R:220,G:220,B:220,A:255).
    /// </summary>
    const Color Gainsboro;

    /// <summary>
    /// GhostWhite color (R:248,G:248,B:255,A:255).
    /// </summary>
    const Color GhostWhite;
    /// <summary>
    /// Gold color (R:255,G:215,B:0,A:255).
    /// </summary>
    const Color Gold;

    /// <summary>
    /// Goldenrod color (R:218,G:165,B:32,A:255).
    /// </summary>
    const Color Goldenrod;

    /// <summary>
    /// Gray color (R:128,G:128,B:128,A:255).
    /// </summary>
    const Color Gray;

    /// <summary>
    /// Green color (R:0,G:128,B:0,A:255).
    /// </summary>
    const Color Green;

    /// <summary>
    /// GreenYellow color (R:173,G:255,B:47,A:255).
    /// </summary>
    const Color GreenYellow;

    /// <summary>
    /// Honeydew color (R:240,G:255,B:240,A:255).
    /// </summary>
    const Color Honeydew;

    /// <summary>
    /// HotPink color (R:255,G:105,B:180,A:255).
    /// </summary>
    const Color HotPink;

    /// <summary>
    /// IndianRed color (R:205,G:92,B:92,A:255).
    /// </summary>
    const Color IndianRed;

    /// <summary>
    /// Indigo color (R:75,G:0,B:130,A:255).
    /// </summary>
    const Color Indigo;

    /// <summary>
    /// Ivory color (R:255,G:255,B:240,A:255).
    /// </summary>
    const Color Ivory;

    /// <summary>
    /// Khaki color (R:240,G:230,B:140,A:255).
    /// </summary>
    const Color Khaki;

    /// <summary>
    /// Lavender color (R:230,G:230,B:250,A:255).
    /// </summary>
    const Color Lavender;

    /// <summary>
    /// LavenderBlush color (R:255,G:240,B:245,A:255).
    /// </summary>
    const Color LavenderBlush;

    /// <summary>
    /// LawnGreen color (R:124,G:252,B:0,A:255).
    /// </summary>
    const Color LawnGreen;

    /// <summary>
    /// LemonChiffon color (R:255,G:250,B:205,A:255).
    /// </summary>
    const Color LemonChiffon;

    /// <summary>
    /// LightBlue color (R:173,G:216,B:230,A:255).
    /// </summary>
    const Color LightBlue;

    /// <summary>
    /// LightCoral color (R:240,G:128,B:128,A:255).
    /// </summary>
    const Color LightCoral;

    /// <summary>
    /// LightCyan color (R:224,G:255,B:255,A:255).
    /// </summary>
    const Color LightCyan;

    /// <summary>
    /// LightGoldenrodYellow color (R:250,G:250,B:210,A:255).
    /// </summary>
    const Color LightGoldenrodYellow;

    /// <summary>
    /// LightGray color (R:211,G:211,B:211,A:255).
    /// </summary>
    const Color LightGray;

    /// <summary>
    /// LightGreen color (R:144,G:238,B:144,A:255).
    /// </summary>
    const Color LightGreen;

    /// <summary>
    /// LightPink color (R:255,G:182,B:193,A:255).
    /// </summary>
    const Color LightPink;

    /// <summary>
    /// LightSalmon color (R:255,G:160,B:122,A:255).
    /// </summary>
    const Color LightSalmon;

    /// <summary>
    /// LightSeaGreen color (R:32,G:178,B:170,A:255).
    /// </summary>
    const Color LightSeaGreen;

    /// <summary>
    /// LightSkyBlue color (R:135,G:206,B:250,A:255).
    /// </summary>
    const Color LightSkyBlue;

    /// <summary>
    /// LightSlateGray color (R:119,G:136,B:153,A:255).
    /// </summary>
    const Color LightSlateGray;

    /// <summary>
    /// LightSteelBlue color (R:176,G:196,B:222,A:255).
    /// </summary>
    const Color LightSteelBlue;

    /// <summary>
    /// LightYellow color (R:255,G:255,B:224,A:255).
    /// </summary>
    const Color LightYellow;

    /// <summary>
    /// Lime color (R:0,G:255,B:0,A:255).
    /// </summary>
    const Color Lime;

    /// <summary>
    /// LimeGreen color (R:50,G:205,B:50,A:255).
    /// </summary>
    const Color LimeGreen;

    /// <summary>
    /// Linen color (R:250,G:240,B:230,A:255).
    /// </summary>
    const Color Linen;

    /// <summary>
    /// Magenta color (R:255,G:0,B:255,A:255).
    /// </summary>
    const Color Magenta;

    /// <summary>
    /// Maroon color (R:128,G:0,B:0,A:255).
    /// </summary>
    const Color Maroon;

    /// <summary>
    /// MediumAquamarine color (R:102,G:205,B:170,A:255).
    /// </summary>
    const Color MediumAquamarine;

    /// <summary>
    /// MediumBlue color (R:0,G:0,B:205,A:255).
    /// </summary>
    const Color MediumBlue;

    /// <summary>
    /// MediumOrchid color (R:186,G:85,B:211,A:255).
    /// </summary>
    const Color MediumOrchid;

    /// <summary>
    /// MediumPurple color (R:147,G:112,B:219,A:255).
    /// </summary>
    const Color MediumPurple;

    /// <summary>
    /// MediumSeaGreen color (R:60,G:179,B:113,A:255).
    /// </summary>
    const Color MediumSeaGreen;

    /// <summary>
    /// MediumSlateBlue color (R:123,G:104,B:238,A:255).
    /// </summary>
    const Color MediumSlateBlue;

    /// <summary>
    /// MediumSpringGreen color (R:0,G:250,B:154,A:255).
    /// </summary>
    const Color MediumSpringGreen;

    /// <summary>
    /// MediumTurquoise color (R:72,G:209,B:204,A:255).
    /// </summary>
    const Color MediumTurquoise;

    /// <summary>
    /// MediumVioletRed color (R:199,G:21,B:133,A:255).
    /// </summary>
    const Color MediumVioletRed;

    /// <summary>
    /// MidnightBlue color (R:25,G:25,B:112,A:255).
    /// </summary>
    const Color MidnightBlue;

    /// <summary>
    /// MintCream color (R:245,G:255,B:250,A:255).
    /// </summary>
    const Color MintCream;

    /// <summary>
    /// MistyRose color (R:255,G:228,B:225,A:255).
    /// </summary>
    const Color MistyRose;

    /// <summary>
    /// Moccasin color (R:255,G:228,B:181,A:255).
    /// </summary>
    const Color Moccasin;

    /// <summary>
    /// MonoGame orange theme color (R:231,G:60,B:0,A:255).
    /// </summary>
    const Color MonoGameOrange;

    /// <summary>
    /// NavajoWhite color (R:255,G:222,B:173,A:255).
    /// </summary>
    const Color NavajoWhite;

    /// <summary>
    /// Navy color (R:0,G:0,B:128,A:255).
    /// </summary>
    const Color Navy;

    /// <summary>
    /// OldLace color (R:253,G:245,B:230,A:255).
    /// </summary>
    const Color OldLace;

    /// <summary>
    /// Olive color (R:128,G:128,B:0,A:255).
    /// </summary>
    const Color Olive;

    /// <summary>
    /// OliveDrab color (R:107,G:142,B:35,A:255).
    /// </summary>
    const Color OliveDrab;

    /// <summary>
    /// Orange color (R:255,G:165,B:0,A:255).
    /// </summary>
    const Color Orange;

    /// <summary>
    /// OrangeRed color (R:255,G:69,B:0,A:255).
    /// </summary>
    const Color OrangeRed;

    /// <summary>
    /// Orchid color (R:218,G:112,B:214,A:255).
    /// </summary>
    const Color Orchid;

    /// <summary>
    /// PaleGoldenrod color (R:238,G:232,B:170,A:255).
    /// </summary>
    const Color PaleGoldenrod;

    /// <summary>
    /// PaleGreen color (R:152,G:251,B:152,A:255).
    /// </summary>
    const Color PaleGreen;

    /// <summary>
    /// PaleTurquoise color (R:175,G:238,B:238,A:255).
    /// </summary>
    const Color PaleTurquoise;
    /// <summary>
    /// PaleVioletRed color (R:219,G:112,B:147,A:255).
    /// </summary>
    const Color PaleVioletRed;

    /// <summary>
    /// PapayaWhip color (R:255,G:239,B:213,A:255).
    /// </summary>
    const Color PapayaWhip;

    /// <summary>
    /// PeachPuff color (R:255,G:218,B:185,A:255).
    /// </summary>
    const Color PeachPuff;

    /// <summary>
    /// Peru color (R:205,G:133,B:63,A:255).
    /// </summary>
    const Color Peru;

    /// <summary>
    /// Pink color (R:255,G:192,B:203,A:255).
    /// </summary>
    const Color Pink;

    /// <summary>
    /// Plum color (R:221,G:160,B:221,A:255).
    /// </summary>
    const Color Plum;

    /// <summary>
    /// PowderBlue color (R:176,G:224,B:230,A:255).
    /// </summary>
    const Color PowderBlue;

    /// <summary>
    ///  Purple color (R:128,G:0,B:128,A:255).
    /// </summary>
    const Color Purple;

    /// <summary>
    /// Red color (R:255,G:0,B:0,A:255).
    /// </summary>
    const Color Red;

    /// <summary>
    /// RosyBrown color (R:188,G:143,B:143,A:255).
    /// </summary>
    const Color RosyBrown;

    /// <summary>
    /// RoyalBlue color (R:65,G:105,B:225,A:255).
    /// </summary>
    const Color RoyalBlue;

    /// <summary>
    /// SaddleBrown color (R:139,G:69,B:19,A:255).
    /// </summary>
    const Color SaddleBrown;

    /// <summary>
    /// Salmon color (R:250,G:128,B:114,A:255).
    /// </summary>
    const Color Salmon;

    /// <summary>
    /// SandyBrown color (R:244,G:164,B:96,A:255).
    /// </summary>
    const Color SandyBrown;

    /// <summary>
    /// SeaGreen color (R:46,G:139,B:87,A:255).
    /// </summary>
    const Color SeaGreen;

    /// <summary>
    /// SeaShell color (R:255,G:245,B:238,A:255).
    /// </summary>
    const Color SeaShell;

    /// <summary>
    /// Sienna color (R:160,G:82,B:45,A:255).
    /// </summary>
    const Color Sienna;

    /// <summary>
    /// Silver color (R:192,G:192,B:192,A:255).
    /// </summary>
    const Color Silver;

    /// <summary>
    /// SkyBlue color (R:135,G:206,B:235,A:255).
    /// </summary>
    const Color SkyBlue;

    /// <summary>
    /// SlateBlue color (R:106,G:90,B:205,A:255).
    /// </summary>
    const Color SlateBlue;

    /// <summary>
    /// SlateGray color (R:112,G:128,B:144,A:255).
    /// </summary>
    const Color SlateGray;

    /// <summary>
    /// Snow color (R:255,G:250,B:250,A:255).
    /// </summary>
    const Color Snow;

    /// <summary>
    /// SpringGreen color (R:0,G:255,B:127,A:255).
    /// </summary>
    const Color SpringGreen;

    /// <summary>
    /// SteelBlue color (R:70,G:130,B:180,A:255).
    /// </summary>
    const Color SteelBlue;

    /// <summary>
    /// Tan color (R:210,G:180,B:140,A:255).
    /// </summary>
    const Color Tan;

    /// <summary>
    /// Teal color (R:0,G:128,B:128,A:255).
    /// </summary>
    const Color Teal;

    /// <summary>
    /// Thistle color (R:216,G:191,B:216,A:255).
    /// </summary>
    const Color Thistle;

    /// <summary>
    /// Tomato color (R:255,G:99,B:71,A:255).
    /// </summary>
    const Color Tomato;

    /// <summary>
    /// Turquoise color (R:64,G:224,B:208,A:255).
    /// </summary>
    const Color Turquoise;

    /// <summary>
    /// Violet color (R:238,G:130,B:238,A:255).
    /// </summary>
    const Color Violet;

    /// <summary>
    /// Wheat color (R:245,G:222,B:179,A:255).
    /// </summary>
    const Color Wheat;

    /// <summary>
    /// White color (R:255,G:255,B:255,A:255).
    /// </summary>
    const Color White;

    /// <summary>
    /// WhiteSmoke color (R:245,G:245,B:245,A:255).
    /// </summary>
    const Color WhiteSmoke;

    /// <summary>
    /// Yellow color (R:255,G:255,B:0,A:255).
    /// </summary>
    const Color Yellow;

    /// <summary>
    /// YellowGreen color (R:154,G:205,B:50,A:255).
    /// </summary>
    const Color YellowGreen;

    ColorPalette() :
        TransparentBlack(Color(0)),
        Transparent(Color(0)),
        AliceBlue(Color(0xfffff8f0)),
        AntiqueWhite(Color(0xffd7ebfa)),
        Aqua(Color(0xffffff00)),
        Aquamarine(Color(0xffd4ff7f)),
        Azure(Color(0xfffffff0)),
        Beige(Color(0xffdcf5f5)),
        Bisque(Color(0xffc4e4ff)),
        Black(Color(0xff000000)),
        BlanchedAlmond(Color(0xffcdebff)),
        Blue(Color(0xffff0000)),
        BlueViolet(Color(0xffe22b8a)),
        Brown(Color(0xff2a2aa5)),
        BurlyWood(Color(0xff87b8de)),
        CadetBlue(Color(0xffa09e5f)),
        Chartreuse(Color(0xff00ff7f)),
        Chocolate(Color(0xff1e69d2)),
        Coral(Color(0xff507fff)),
        CornflowerBlue(Color(0xffed9564)),
        Cornsilk(Color(0xffdcf8ff)),
        Crimson(Color(0xff3c14dc)),
        Cyan(Color(0xffffff00)),
        DarkBlue(Color(0xff8b0000)),
        DarkCyan(Color(0xff8b8b00)),
        DarkGoldenrod(Color(0xff0b86b8)),
        DarkGray(Color(0xffa9a9a9)),
        DarkGreen(Color(0xff006400)),
        DarkKhaki(Color(0xff6bb7bd)),
        DarkMagenta(Color(0xff8b008b)),
        DarkOliveGreen(Color(0xff2f6b55)),
        DarkOrange(Color(0xff008cff)),
        DarkOrchid(Color(0xffcc3299)),
        DarkRed(Color(0xff00008b)),
        DarkSalmon(Color(0xff7a96e9)),
        DarkSeaGreen(Color(0xff8bbc8f)),
        DarkSlateBlue(Color(0xff8b3d48)),
        DarkSlateGray(Color(0xff4f4f2f)),
        DarkTurquoise(Color(0xffd1ce00)),
        DarkViolet(Color(0xffd30094)),
        DeepPink(Color(0xff9314ff)),
        DeepSkyBlue(Color(0xffffbf00)),
        DimGray(Color(0xff696969)),
        DodgerBlue(Color(0xffff901e)),
        Firebrick(Color(0xff2222b2)),
        FloralWhite(Color(0xfff0faff)),
        ForestGreen(Color(0xff228b22)),
        Fuchsia(Color(0xffff00ff)),
        Gainsboro(Color(0xffdcdcdc)),
        GhostWhite(Color(0xfffff8f8)),
        Gold(Color(0xff00d7ff)),
        Goldenrod(Color(0xff20a5da)),
        Gray(Color(0xff808080)),
        Green(Color(0xff008000)),
        GreenYellow(Color(0xff2fffad)),
        Honeydew(Color(0xfff0fff0)),
        HotPink(Color(0xffb469ff)),
        IndianRed(Color(0xff5c5ccd)),
        Indigo(Color(0xff82004b)),
        Ivory(Color(0xfff0ffff)),
        Khaki(Color(0xff8ce6f0)),
        Lavender(Color(0xfffae6e6)),
        LavenderBlush(Color(0xfff5f0ff)),
        LawnGreen(Color(0xff00fc7c)),
        LemonChiffon(Color(0xffcdfaff)),
        LightBlue(Color(0xffe6d8ad)),
        LightCoral(Color(0xff8080f0)),
        LightCyan(Color(0xffffffe0)),
        LightGoldenrodYellow(Color(0xffd2fafa)),
        LightGray(Color(0xffd3d3d3)),
        LightGreen(Color(0xff90ee90)),
        LightPink(Color(0xffc1b6ff)),
        LightSalmon(Color(0xff7aa0ff)),
        LightSeaGreen(Color(0xffaab220)),
        LightSkyBlue(Color(0xffface87)),
        LightSlateGray(Color(0xff998877)),
        LightSteelBlue(Color(0xffdec4b0)),
        LightYellow(Color(0xffe0ffff)),
        Lime(Color(0xff00ff00)),
        LimeGreen(Color(0xff32cd32)),
        Linen(Color(0xffe6f0fa)),
        Magenta(Color(0xffff00ff)),
        Maroon(Color(0xff000080)),
        MediumAquamarine(Color(0xffaacd66)),
        MediumBlue(Color(0xffcd0000)),
        MediumOrchid(Color(0xffd355ba)),
        MediumPurple(Color(0xffdb7093)),
        MediumSeaGreen(Color(0xff71b33c)),
        MediumSlateBlue(Color(0xffee687b)),
        MediumSpringGreen(Color(0xff9afa00)),
        MediumTurquoise(Color(0xffccd148)),
        MediumVioletRed(Color(0xff8515c7)),
        MidnightBlue(Color(0xff701919)),
        MintCream(Color(0xfffafff5)),
        MistyRose(Color(0xffe1e4ff)),
        Moccasin(Color(0xffb5e4ff)),
        MonoGameOrange(Color(0xff003ce7)),
        NavajoWhite(Color(0xffaddeff)),
        Navy(Color(0xff800000)),
        OldLace(Color(0xffe6f5fd)),
        Olive(Color(0xff008080)),
        OliveDrab(Color(0xff238e6b)),
        Orange(Color(0xff00a5ff)),
        OrangeRed(Color(0xff0045ff)),
        Orchid(Color(0xffd670da)),
        PaleGoldenrod(Color(0xffaae8ee)),
        PaleGreen(Color(0xff98fb98)),
        PaleTurquoise(Color(0xffeeeeaf)),
        PaleVioletRed(Color(0xff9370db)),
        PapayaWhip(Color(0xffd5efff)),
        PeachPuff(Color(0xffb9daff)),
        Peru(Color(0xff3f85cd)),
        Pink(Color(0xffcbc0ff)),
        Plum(Color(0xffdda0dd)),
        PowderBlue(Color(0xffe6e0b0)),
        Purple(Color(0xff800080)),
        Red(Color(0xff0000ff)),
        RosyBrown(Color(0xff8f8fbc)),
        RoyalBlue(Color(0xffe16941)),
        SaddleBrown(Color(0xff13458b)),
        Salmon(Color(0xff7280fa)),
        SandyBrown(Color(0xff60a4f4)),
        SeaGreen(Color(0xff578b2e)),
        SeaShell(Color(0xffeef5ff)),
        Sienna(Color(0xff2d52a0)),
        Silver(Color(0xffc0c0c0)),
        SkyBlue(Color(0xffebce87)),
        SlateBlue(Color(0xffcd5a6a)),
        SlateGray(Color(0xff908070)),
        Snow(Color(0xfffafaff)),
        SpringGreen(Color(0xff7fff00)),
        SteelBlue(Color(0xffb48246)),
        Tan(Color(0xff8cb4d2)),
        Teal(Color(0xff808000)),
        Thistle(Color(0xffd8bfd8)),
        Tomato(Color(0xff4763ff)),
        Turquoise(Color(0xffd0e040)),
        Violet(Color(0xffee82ee)),
        Wheat(Color(0xffb3def5)),
        White(Color(UINT32_MAX)),
        WhiteSmoke(Color(0xfff5f5f5)),
        Yellow(Color(0xff00ffff)),
        YellowGreen(Color(0xff32cd9a))
    {
    }
};

}
