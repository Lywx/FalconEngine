#include <FalconEngine/Graphics/Renderer/Font/BitmapLine.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapGlyph.h>

namespace FalconEngine
{

BitmapLine::BitmapLine(double lineWidth) :
    mLineWidth(lineWidth)
{
}

bool BitmapLine::PushGlyph(const BitmapGlyph& glyph, double fontSizeScale)
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
