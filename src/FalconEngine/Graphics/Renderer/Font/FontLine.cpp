#include <FalconEngine/Graphics/Renderer/Font/FontLine.h>
#include <FalconEngine/Graphics/Renderer/Font/FontGlyph.h>

namespace FalconEngine
{

FontLine::FontLine(double lineWidth) :
    mLineWidth(lineWidth)
{
}

bool FontLine::PushGlyph(const FontGlyph& glyph, double fontSizeScale)
{
    double additionalWidth = glyph.mAdvance * fontSizeScale;
    if (mLineWidthCurrent + additionalWidth <= mLineWidth)
    {
        mLineGlyphs.push_back(glyph);
        mLineWidthCurrent += additionalWidth;
        return true;
    }

    return false;
}

}
