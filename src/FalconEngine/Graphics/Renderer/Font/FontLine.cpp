#include <FalconEngine/Graphics/Renderer/Font/FontLine.h>
#include <FalconEngine/Graphics/Renderer/Font/FontGlyph.h>

namespace FalconEngine
{

FontLine::FontLine(double lineWidth) :
    mWidth(lineWidth)
{
}

bool FontLine::PushGlyph(const FontGlyph& glyph, double fontSizeScale)
{
    double additionalWidth = glyph.mAdvance * fontSizeScale;
    if (mWidthCurrent + additionalWidth <= mWidth)
    {
        mGlyphList.push_back(glyph);
        mWidthCurrent += additionalWidth;
        return true;
    }

    return false;
}

}
