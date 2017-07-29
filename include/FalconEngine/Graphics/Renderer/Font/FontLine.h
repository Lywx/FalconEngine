#pragma once

#include <FalconEngine/Graphics/Common.h>

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

    double                 mWidth;                                        // Maximum width of this line in pixel. The font type specific scaling is already included.
    double                 mWidthCurrent = 0;                             // Width of this line in pixel. The font type specific scaling is already included.

    std::vector<FontGlyph> mGlyphList;
};
#pragma warning(default: 4251)

}
