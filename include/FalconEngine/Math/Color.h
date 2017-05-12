#pragma once

#include <cstdint>
#include <limits>

#include <FalconEngine/Math/Integer.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

class FALCON_ENGINE_ITEM_MATH Color
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit Color(uint32 hex);
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(float r, float g, float b);
    Color(float r, float g, float b, float a);
    Color();

public:
    operator Vector3f() const;
    operator Vector4f() const;

public:
    uint8 R;
    uint8 G;
    uint8 B;
    uint8 A;
};

bool operator==(Color lhs, Color rhs);
bool operator!=(Color lhs, Color rhs);

class FALCON_ENGINE_ITEM_MATH ColorPalette
{
public:
    static const Color TransparentBlack;

    /// <summary>
    /// Transparent color (R:0,G:0,B:0,A:0).
    /// </summary>
    static const Color Transparent;

    /// <summary>
    /// AliceBlue color (R:240,G:248,B:255,A:255).
    /// </summary>
    static const Color AliceBlue;

    /// <summary>
    /// AntiqueWhite color (R:250,G:235,B:215,A:255).
    /// </summary>
    static const Color AntiqueWhite;

    /// <summary>
    /// Aqua color (R:0,G:255,B:255,A:255).
    /// </summary>
    static const Color Aqua;

    /// <summary>
    /// Aquamarine color (R:127,G:255,B:212,A:255).
    /// </summary>
    static const Color Aquamarine;

    /// <summary>
    /// Azure color (R:240,G:255,B:255,A:255).
    /// </summary>
    static const Color Azure;

    /// <summary>
    /// Beige color (R:245,G:245,B:220,A:255).
    /// </summary>
    static const Color Beige;

    /// <summary>
    /// Bisque color (R:255,G:228,B:196,A:255).
    /// </summary>
    static const Color Bisque;

    /// <summary>
    /// Black color (R:0,G:0,B:0,A:255).
    /// </summary>
    static const Color Black;

    /// <summary>
    /// BlanchedAlmond color (R:255,G:235,B:205,A:255).
    /// </summary>
    static const Color BlanchedAlmond;

    /// <summary>
    /// Blue color (R:0,G:0,B:255,A:255).
    /// </summary>
    static const Color Blue;

    /// <summary>
    /// BlueViolet color (R:138,G:43,B:226,A:255).
    /// </summary>
    static const Color BlueViolet;

    /// <summary>
    /// Brown color (R:165,G:42,B:42,A:255).
    /// </summary>
    static const Color Brown;

    /// <summary>
    /// BurlyWood color (R:222,G:184,B:135,A:255).
    /// </summary>
    static const Color BurlyWood;

    /// <summary>
    /// CadetBlue color (R:95,G:158,B:160,A:255).
    /// </summary>
    static const Color CadetBlue;

    /// <summary>
    /// Chartreuse color (R:127,G:255,B:0,A:255).
    /// </summary>
    static const Color Chartreuse;

    /// <summary>
    /// Chocolate color (R:210,G:105,B:30,A:255).
    /// </summary>
    static const Color Chocolate;

    /// <summary>
    /// Coral color (R:255,G:127,B:80,A:255).
    /// </summary>
    static const Color Coral;

    /// <summary>
    /// CornflowerBlue color (R:100,G:149,B:237,A:255).
    /// </summary>
    static const Color CornflowerBlue;

    /// <summary>
    /// Cornsilk color (R:255,G:248,B:220,A:255).
    /// </summary>
    static const Color Cornsilk;

    /// <summary>
    /// Crimson color (R:220,G:20,B:60,A:255).
    /// </summary>
    static const Color Crimson;

    /// <summary>
    /// Cyan color (R:0,G:255,B:255,A:255).
    /// </summary>
    static const Color Cyan;

    /// <summary>
    /// DarkBlue color (R:0,G:0,B:139,A:255).
    /// </summary>
    static const Color DarkBlue;

    /// <summary>
    /// DarkCyan color (R:0,G:139,B:139,A:255).
    /// </summary>
    static const Color DarkCyan;

    /// <summary>
    /// DarkGoldenrod color (R:184,G:134,B:11,A:255).
    /// </summary>
    static const Color DarkGoldenrod;

    /// <summary>
    /// DarkGray color (R:169,G:169,B:169,A:255).
    /// </summary>
    static const Color DarkGray;

    /// <summary>
    /// DarkGreen color (R:0,G:100,B:0,A:255).
    /// </summary>
    static const Color DarkGreen;

    /// <summary>
    /// DarkKhaki color (R:189,G:183,B:107,A:255).
    /// </summary>
    static const Color DarkKhaki;

    /// <summary>
    /// DarkMagenta color (R:139,G:0,B:139,A:255).
    /// </summary>
    static const Color DarkMagenta;

    /// <summary>
    /// DarkOliveGreen color (R:85,G:107,B:47,A:255).
    /// </summary>
    static const Color DarkOliveGreen;

    /// <summary>
    /// DarkOrange color (R:255,G:140,B:0,A:255).
    /// </summary>
    static const Color DarkOrange;

    /// <summary>
    /// DarkOrchid color (R:153,G:50,B:204,A:255).
    /// </summary>
    static const Color DarkOrchid;

    /// <summary>
    /// DarkRed color (R:139,G:0,B:0,A:255).
    /// </summary>
    static const Color DarkRed;

    /// <summary>
    /// DarkSalmon color (R:233,G:150,B:122,A:255).
    /// </summary>
    static const Color DarkSalmon;

    /// <summary>
    /// DarkSeaGreen color (R:143,G:188,B:139,A:255).
    /// </summary>
    static const Color DarkSeaGreen;

    /// <summary>
    /// DarkSlateBlue color (R:72,G:61,B:139,A:255).
    /// </summary>
    static const Color DarkSlateBlue;

    /// <summary>
    /// DarkSlateGray color (R:47,G:79,B:79,A:255).
    /// </summary>
    static const Color DarkSlateGray;

    /// <summary>
    /// DarkTurquoise color (R:0,G:206,B:209,A:255).
    /// </summary>
    static const Color DarkTurquoise;

    /// <summary>
    /// DarkViolet color (R:148,G:0,B:211,A:255).
    /// </summary>
    static const Color DarkViolet;

    /// <summary>
    /// DeepPink color (R:255,G:20,B:147,A:255).
    /// </summary>
    static const Color DeepPink;

    /// <summary>
    /// DeepSkyBlue color (R:0,G:191,B:255,A:255).
    /// </summary>
    static const Color DeepSkyBlue;

    /// <summary>
    /// DimGray color (R:105,G:105,B:105,A:255).
    /// </summary>
    static const Color DimGray;

    /// <summary>
    /// DodgerBlue color (R:30,G:144,B:255,A:255).
    /// </summary>
    static const Color DodgerBlue;

    /// <summary>
    /// Firebrick color (R:178,G:34,B:34,A:255).
    /// </summary>
    static const Color Firebrick;

    /// <summary>
    /// FloralWhite color (R:255,G:250,B:240,A:255).
    /// </summary>
    static const Color FloralWhite;

    /// <summary>
    /// ForestGreen color (R:34,G:139,B:34,A:255).
    /// </summary>
    static const Color ForestGreen;

    /// <summary>
    /// Fuchsia color (R:255,G:0,B:255,A:255).
    /// </summary>
    static const Color Fuchsia;

    /// <summary>
    /// Gainsboro color (R:220,G:220,B:220,A:255).
    /// </summary>
    static const Color Gainsboro;

    /// <summary>
    /// GhostWhite color (R:248,G:248,B:255,A:255).
    /// </summary>
    static const Color GhostWhite;
    /// <summary>
    /// Gold color (R:255,G:215,B:0,A:255).
    /// </summary>
    static const Color Gold;

    /// <summary>
    /// Goldenrod color (R:218,G:165,B:32,A:255).
    /// </summary>
    static const Color Goldenrod;

    /// <summary>
    /// Gray color (R:128,G:128,B:128,A:255).
    /// </summary>
    static const Color Gray;

    /// <summary>
    /// Green color (R:0,G:128,B:0,A:255).
    /// </summary>
    static const Color Green;

    /// <summary>
    /// GreenYellow color (R:173,G:255,B:47,A:255).
    /// </summary>
    static const Color GreenYellow;

    /// <summary>
    /// Honeydew color (R:240,G:255,B:240,A:255).
    /// </summary>
    static const Color Honeydew;

    /// <summary>
    /// HotPink color (R:255,G:105,B:180,A:255).
    /// </summary>
    static const Color HotPink;

    /// <summary>
    /// IndianRed color (R:205,G:92,B:92,A:255).
    /// </summary>
    static const Color IndianRed;

    /// <summary>
    /// Indigo color (R:75,G:0,B:130,A:255).
    /// </summary>
    static const Color Indigo;

    /// <summary>
    /// Ivory color (R:255,G:255,B:240,A:255).
    /// </summary>
    static const Color Ivory;

    /// <summary>
    /// Khaki color (R:240,G:230,B:140,A:255).
    /// </summary>
    static const Color Khaki;

    /// <summary>
    /// Lavender color (R:230,G:230,B:250,A:255).
    /// </summary>
    static const Color Lavender;

    /// <summary>
    /// LavenderBlush color (R:255,G:240,B:245,A:255).
    /// </summary>
    static const Color LavenderBlush;

    /// <summary>
    /// LawnGreen color (R:124,G:252,B:0,A:255).
    /// </summary>
    static const Color LawnGreen;

    /// <summary>
    /// LemonChiffon color (R:255,G:250,B:205,A:255).
    /// </summary>
    static const Color LemonChiffon;

    /// <summary>
    /// LightBlue color (R:173,G:216,B:230,A:255).
    /// </summary>
    static const Color LightBlue;

    /// <summary>
    /// LightCoral color (R:240,G:128,B:128,A:255).
    /// </summary>
    static const Color LightCoral;

    /// <summary>
    /// LightCyan color (R:224,G:255,B:255,A:255).
    /// </summary>
    static const Color LightCyan;

    /// <summary>
    /// LightGoldenrodYellow color (R:250,G:250,B:210,A:255).
    /// </summary>
    static const Color LightGoldenrodYellow;

    /// <summary>
    /// LightGray color (R:211,G:211,B:211,A:255).
    /// </summary>
    static const Color LightGray;

    /// <summary>
    /// LightGreen color (R:144,G:238,B:144,A:255).
    /// </summary>
    static const Color LightGreen;

    /// <summary>
    /// LightPink color (R:255,G:182,B:193,A:255).
    /// </summary>
    static const Color LightPink;

    /// <summary>
    /// LightSalmon color (R:255,G:160,B:122,A:255).
    /// </summary>
    static const Color LightSalmon;

    /// <summary>
    /// LightSeaGreen color (R:32,G:178,B:170,A:255).
    /// </summary>
    static const Color LightSeaGreen;

    /// <summary>
    /// LightSkyBlue color (R:135,G:206,B:250,A:255).
    /// </summary>
    static const Color LightSkyBlue;

    /// <summary>
    /// LightSlateGray color (R:119,G:136,B:153,A:255).
    /// </summary>
    static const Color LightSlateGray;

    /// <summary>
    /// LightSteelBlue color (R:176,G:196,B:222,A:255).
    /// </summary>
    static const Color LightSteelBlue;

    /// <summary>
    /// LightYellow color (R:255,G:255,B:224,A:255).
    /// </summary>
    static const Color LightYellow;

    /// <summary>
    /// Lime color (R:0,G:255,B:0,A:255).
    /// </summary>
    static const Color Lime;

    /// <summary>
    /// LimeGreen color (R:50,G:205,B:50,A:255).
    /// </summary>
    static const Color LimeGreen;

    /// <summary>
    /// Linen color (R:250,G:240,B:230,A:255).
    /// </summary>
    static const Color Linen;

    /// <summary>
    /// Magenta color (R:255,G:0,B:255,A:255).
    /// </summary>
    static const Color Magenta;

    /// <summary>
    /// Maroon color (R:128,G:0,B:0,A:255).
    /// </summary>
    static const Color Maroon;

    /// <summary>
    /// MediumAquamarine color (R:102,G:205,B:170,A:255).
    /// </summary>
    static const Color MediumAquamarine;

    /// <summary>
    /// MediumBlue color (R:0,G:0,B:205,A:255).
    /// </summary>
    static const Color MediumBlue;

    /// <summary>
    /// MediumOrchid color (R:186,G:85,B:211,A:255).
    /// </summary>
    static const Color MediumOrchid;

    /// <summary>
    /// MediumPurple color (R:147,G:112,B:219,A:255).
    /// </summary>
    static const Color MediumPurple;

    /// <summary>
    /// MediumSeaGreen color (R:60,G:179,B:113,A:255).
    /// </summary>
    static const Color MediumSeaGreen;

    /// <summary>
    /// MediumSlateBlue color (R:123,G:104,B:238,A:255).
    /// </summary>
    static const Color MediumSlateBlue;

    /// <summary>
    /// MediumSpringGreen color (R:0,G:250,B:154,A:255).
    /// </summary>
    static const Color MediumSpringGreen;

    /// <summary>
    /// MediumTurquoise color (R:72,G:209,B:204,A:255).
    /// </summary>
    static const Color MediumTurquoise;

    /// <summary>
    /// MediumVioletRed color (R:199,G:21,B:133,A:255).
    /// </summary>
    static const Color MediumVioletRed;

    /// <summary>
    /// MidnightBlue color (R:25,G:25,B:112,A:255).
    /// </summary>
    static const Color MidnightBlue;

    /// <summary>
    /// MintCream color (R:245,G:255,B:250,A:255).
    /// </summary>
    static const Color MintCream;

    /// <summary>
    /// MistyRose color (R:255,G:228,B:225,A:255).
    /// </summary>
    static const Color MistyRose;

    /// <summary>
    /// Moccasin color (R:255,G:228,B:181,A:255).
    /// </summary>
    static const Color Moccasin;

    /// <summary>
    /// MonoGame orange theme color (R:231,G:60,B:0,A:255).
    /// </summary>
    static const Color MonoGameOrange;

    /// <summary>
    /// NavajoWhite color (R:255,G:222,B:173,A:255).
    /// </summary>
    static const Color NavajoWhite;

    /// <summary>
    /// Navy color (R:0,G:0,B:128,A:255).
    /// </summary>
    static const Color Navy;

    /// <summary>
    /// OldLace color (R:253,G:245,B:230,A:255).
    /// </summary>
    static const Color OldLace;

    /// <summary>
    /// Olive color (R:128,G:128,B:0,A:255).
    /// </summary>
    static const Color Olive;

    /// <summary>
    /// OliveDrab color (R:107,G:142,B:35,A:255).
    /// </summary>
    static const Color OliveDrab;

    /// <summary>
    /// Orange color (R:255,G:165,B:0,A:255).
    /// </summary>
    static const Color Orange;

    /// <summary>
    /// OrangeRed color (R:255,G:69,B:0,A:255).
    /// </summary>
    static const Color OrangeRed;

    /// <summary>
    /// Orchid color (R:218,G:112,B:214,A:255).
    /// </summary>
    static const Color Orchid;

    /// <summary>
    /// PaleGoldenrod color (R:238,G:232,B:170,A:255).
    /// </summary>
    static const Color PaleGoldenrod;

    /// <summary>
    /// PaleGreen color (R:152,G:251,B:152,A:255).
    /// </summary>
    static const Color PaleGreen;

    /// <summary>
    /// PaleTurquoise color (R:175,G:238,B:238,A:255).
    /// </summary>
    static const Color PaleTurquoise;
    /// <summary>
    /// PaleVioletRed color (R:219,G:112,B:147,A:255).
    /// </summary>
    static const Color PaleVioletRed;

    /// <summary>
    /// PapayaWhip color (R:255,G:239,B:213,A:255).
    /// </summary>
    static const Color PapayaWhip;

    /// <summary>
    /// PeachPuff color (R:255,G:218,B:185,A:255).
    /// </summary>
    static const Color PeachPuff;

    /// <summary>
    /// Peru color (R:205,G:133,B:63,A:255).
    /// </summary>
    static const Color Peru;

    /// <summary>
    /// Pink color (R:255,G:192,B:203,A:255).
    /// </summary>
    static const Color Pink;

    /// <summary>
    /// Plum color (R:221,G:160,B:221,A:255).
    /// </summary>
    static const Color Plum;

    /// <summary>
    /// PowderBlue color (R:176,G:224,B:230,A:255).
    /// </summary>
    static const Color PowderBlue;

    /// <summary>
    ///  Purple color (R:128,G:0,B:128,A:255).
    /// </summary>
    static const Color Purple;

    /// <summary>
    /// Red color (R:255,G:0,B:0,A:255).
    /// </summary>
    static const Color Red;

    /// <summary>
    /// RosyBrown color (R:188,G:143,B:143,A:255).
    /// </summary>
    static const Color RosyBrown;

    /// <summary>
    /// RoyalBlue color (R:65,G:105,B:225,A:255).
    /// </summary>
    static const Color RoyalBlue;

    /// <summary>
    /// SaddleBrown color (R:139,G:69,B:19,A:255).
    /// </summary>
    static const Color SaddleBrown;

    /// <summary>
    /// Salmon color (R:250,G:128,B:114,A:255).
    /// </summary>
    static const Color Salmon;

    /// <summary>
    /// SandyBrown color (R:244,G:164,B:96,A:255).
    /// </summary>
    static const Color SandyBrown;

    /// <summary>
    /// SeaGreen color (R:46,G:139,B:87,A:255).
    /// </summary>
    static const Color SeaGreen;

    /// <summary>
    /// SeaShell color (R:255,G:245,B:238,A:255).
    /// </summary>
    static const Color SeaShell;

    /// <summary>
    /// Sienna color (R:160,G:82,B:45,A:255).
    /// </summary>
    static const Color Sienna;

    /// <summary>
    /// Silver color (R:192,G:192,B:192,A:255).
    /// </summary>
    static const Color Silver;

    /// <summary>
    /// SkyBlue color (R:135,G:206,B:235,A:255).
    /// </summary>
    static const Color SkyBlue;

    /// <summary>
    /// SlateBlue color (R:106,G:90,B:205,A:255).
    /// </summary>
    static const Color SlateBlue;

    /// <summary>
    /// SlateGray color (R:112,G:128,B:144,A:255).
    /// </summary>
    static const Color SlateGray;

    /// <summary>
    /// Snow color (R:255,G:250,B:250,A:255).
    /// </summary>
    static const Color Snow;

    /// <summary>
    /// SpringGreen color (R:0,G:255,B:127,A:255).
    /// </summary>
    static const Color SpringGreen;

    /// <summary>
    /// SteelBlue color (R:70,G:130,B:180,A:255).
    /// </summary>
    static const Color SteelBlue;

    /// <summary>
    /// Tan color (R:210,G:180,B:140,A:255).
    /// </summary>
    static const Color Tan;

    /// <summary>
    /// Teal color (R:0,G:128,B:128,A:255).
    /// </summary>
    static const Color Teal;

    /// <summary>
    /// Thistle color (R:216,G:191,B:216,A:255).
    /// </summary>
    static const Color Thistle;

    /// <summary>
    /// Tomato color (R:255,G:99,B:71,A:255).
    /// </summary>
    static const Color Tomato;

    /// <summary>
    /// Turquoise color (R:64,G:224,B:208,A:255).
    /// </summary>
    static const Color Turquoise;

    /// <summary>
    /// Violet color (R:238,G:130,B:238,A:255).
    /// </summary>
    static const Color Violet;

    /// <summary>
    /// Wheat color (R:245,G:222,B:179,A:255).
    /// </summary>
    static const Color Wheat;

    /// <summary>
    /// White color (R:255,G:255,B:255,A:255).
    /// </summary>
    static const Color White;

    /// <summary>
    /// WhiteSmoke color (R:245,G:245,B:245,A:255).
    /// </summary>
    static const Color WhiteSmoke;

    /// <summary>
    /// Yellow color (R:255,G:255,B:0,A:255).
    /// </summary>
    static const Color Yellow;

    /// <summary>
    /// YellowGreen color (R:154,G:205,B:50,A:255).
    /// </summary>
    static const Color YellowGreen;
};

Color
Transparent(Color color, float a);

Color
Transparent(Color color, uint8 a);

}
