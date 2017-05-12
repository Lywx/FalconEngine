#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

namespace FalconEngine
{

class BitmapGlyph;

#pragma warning(disable: 4251)
class BitmapLine
{
public:
    BitmapLine(double lineWidth);

    bool PushGlyph(const BitmapGlyph& glyph, double fontSizeScale);

    double                   mLineWidth;                                        // Maximum width of this line in pixel. The font type specific scaling is already included.
    double                   mLineWidthCurrent = 0;                             // Width of this line in pixel. The font type specific scaling is already included.

    std::vector<BitmapGlyph> mLineGlyphs;
};
#pragma warning(default: 4251)

}
