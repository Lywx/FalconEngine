#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <FalconEngine/Graphics/Renderer/Font/Font.h>
#include <FalconEngine/Graphics/Renderer/Font/FontLine.h>
#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class FontData
{
public:
    static void
    FillFont(_IN_     unsigned char                 *bufferData,
             _IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,

             _IN_ const FontGlyph *glyph,
             _IN_ Vector4f         glyphColor,

             _IN_ double fontSizeScale)
    {
        // Font color
        bufferAdaptor->Fill<Vector4f>(bufferData, glyphColor);

        // NOTE(Wuxiang): 1.32 is value the when imported font size is 33. 1.32 is
        // used as origin for scaling.

        // Font width
        bufferAdaptor->FillAs<double, float>(bufferData, 0.50 * (1 + 0.15 * (fontSizeScale - 1.32)));

        // Font edge
        bufferAdaptor->FillAs<double, float>(bufferData, 0.03 / (1 + 1.05 * (fontSizeScale - 1.32)));

        // Font page
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mPage);
    }

    static void
    FillGlyph(
        _IN_     unsigned char                 *bufferData,
        _IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,

        _IN_ const FontGlyph *glyph,
        _IN_ Vector4f         glyphColor,
        _IN_ float            glyphPosX,
        _IN_ float            glyphPosY,

        _IN_ const Font *font,
        _IN_ double      fontSizeScale)
    {
        // NOTE(Wuxiang): Since x1, y1 represents left-bottom coordinate, we need to
        // process base and yoffset differently. Notably, x1 is amended to center the
        // glyph for different width, 'x + advance / 2 - width / 2' is the x1
        // considering no x offset. I don't think this cause the glyph to draw as
        // monospaced, since the advance would be different for different character
        // set, which means English would have different advance than Chinese.
        // However, the influence of width indeed is compensated using this method in
        // spacing of the glyph.
        double x1 = glyphPosX + (glyph->mAdvance / 2 - glyph->mWidth / 2 + glyph->mOffsetX) * fontSizeScale;
        double y2 = glyphPosY + (font->mLineBase - glyph->mOffsetY) * fontSizeScale;
        double y1 = y2 - glyph->mHeight * fontSizeScale;
        double x2 = x1 + glyph->mWidth * fontSizeScale;

        bufferAdaptor->FillAs<double, float>(bufferData, x1);
        bufferAdaptor->FillAs<double, float>(bufferData, y1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT1);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);

        bufferAdaptor->FillAs<double, float>(bufferData, x2);
        bufferAdaptor->FillAs<double, float>(bufferData, y2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT2);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);

        bufferAdaptor->FillAs<double, float>(bufferData, x1);
        bufferAdaptor->FillAs<double, float>(bufferData, y2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT2);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);

        bufferAdaptor->FillAs<double, float>(bufferData, x2);
        bufferAdaptor->FillAs<double, float>(bufferData, y1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT1);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);

        bufferAdaptor->FillAs<double, float>(bufferData, x2);
        bufferAdaptor->FillAs<double, float>(bufferData, y2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS2);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT2);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);

        bufferAdaptor->FillAs<double, float>(bufferData, x1);
        bufferAdaptor->FillAs<double, float>(bufferData, y1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mS1);
        bufferAdaptor->FillAs<double, float>(bufferData, glyph->mT1);
        FillFont(bufferData, bufferAdaptor, glyph, glyphColor, fontSizeScale);
    }

    // @summary Fill the vertex buffer with the text line information.
    static void
    FillTextLines(
        _IN_     unsigned char                 *bufferData,
        _IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,

        _IN_  const Font             *font,
        _IN_  float                   fontSize,

        _IN_  Vector2f                     textPosition,
        _IN_  Vector4f                     textColor,
        _IN_  const std::vector<FontLine>& textLines)
    {
        float x = textPosition.x;
        float y = textPosition.y;

        double fontSizeScale = fontSize / font->mSizePt;

        for(auto& line : textLines)
        {
            for (auto& glyph : line.mLineGlyphs)
            {
                FillGlyph(bufferData, bufferAdaptor, &glyph, textColor, x, y, font, fontSizeScale);

                x += float(glyph.mAdvance * fontSizeScale);
            }

            x = textPosition.x;
            y -= float(font->mLineHeight * fontSizeScale);
        }
    }


    // @summary Construct all the necessary lexical separation of given text into
    // lines of words.
    //
    // @return The glyph number inside the text lines.
    static int
    CreateTextLines(
        _IN_  const Font *font,
        _IN_  const FontText        *text,
        _OUT_ std::vector<FontLine>& textLines)
    {
        using namespace boost;

        static auto sTextLineStrings = std::vector<std::wstring>();
        sTextLineStrings.clear();

        // Split string into lines.
        split(sTextLineStrings, text->mTextString, is_any_of(L"\n"));

        // Bounds is formatted as [x, y, width, height]
        const auto textLineWidth = text->mTextBounds[2];

        int glyphCount = 0;
        auto textLineCurrent = FontLine(textLineWidth);
        int textLineNum = int(sTextLineStrings.size());
        for (int textLineIndex = 0; textLineIndex < textLineNum; ++textLineIndex)
        {
            for (const wchar_t& c : sTextLineStrings[textLineIndex])
            {
                // NOTE(Wuxiang): When processing English, a word is defined as space
                // separated letters. But this concept would not work
                // on Chinese, when You still need to crop the word when the maximum line
                // width is exceeded. The arbitrariness exists here for English or
                // Chinese. If you don't have the pre-knowledge you won't be able to
                // decide which way is correct. My decision here is to leave this to
                // higher level code to preprocess this kind of information. This function
                // only deals new line characters.

                Uint32 glyphCodepoint = c;
                auto   glyphIndex = font->mGlyphIndexTable.at(glyphCodepoint);
                auto&  glyph = font->mGlyphTable.at(glyphIndex);
                ++glyphCount;

                double fontSizeScale = text->mFontSize / font->mSizePt;
                bool success = textLineCurrent.PushGlyph(glyph, fontSizeScale);
                if (!success)
                {
                    // Have to start a new line for this glyph
                    textLines.push_back(textLineCurrent);
                    textLineCurrent = FontLine(textLineWidth);
                    textLineCurrent.PushGlyph(glyph, fontSizeScale);
                }
            }

            // NOTE(Wuxiang): There will be at least one line even the string is empty.
            textLines.push_back(textLineCurrent);
        }

        return glyphCount;
    }
};


}
