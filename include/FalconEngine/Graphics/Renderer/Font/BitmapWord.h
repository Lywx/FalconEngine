#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <FalconEngine/Graphics/Renderer/Font/BitmapGlyph.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class BitmapWord
{
public:
    BitmapWord(double fontScale);

    double                   mFontSizeScale;                                    // Font up-scaling based on font type and font size
    std::vector<BitmapGlyph> mWordLetters;                                      // Collection of letters used in the word, allow duplication
    double                   mWordWidth;                                        // Width of the word in pixel. The font type specific scaling is already included.
};
#pragma warning(default: 4251)

}

