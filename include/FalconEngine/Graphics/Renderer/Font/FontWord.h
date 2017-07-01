#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <FalconEngine/Graphics/Renderer/Font/FontGlyph.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API FontWord
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    explicit FontWord(double fontScale);

public:
    double                 mFontSizeScale;                                    // Font up-scaling based on font type and font size
    std::vector<FontGlyph> mWordLetters;                                      // Collection of letters used in the word, allow duplication
    double                 mWordWidth;                                        // Width of the word in pixel. The font type specific scaling is already included.
};
#pragma warning(default: 4251)

}

