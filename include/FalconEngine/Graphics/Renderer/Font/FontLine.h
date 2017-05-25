#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <vector>

namespace FalconEngine
{

class FontGlyph;

#pragma warning(disable: 4251)
class FontLine
{
public:
    explicit FontLine(double lineWidth);

public:
    bool
    PushGlyph(const FontGlyph& glyph, double fontSizeScale);

    double                 mLineWidth;                                        // Maximum width of this line in pixel. The font type specific scaling is already included.
    double                 mLineWidthCurrent = 0;                             // Width of this line in pixel. The font type specific scaling is already included.

    std::vector<FontGlyph> mLineGlyphs;
};
#pragma warning(default: 4251)

}
