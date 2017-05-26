#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>

#include <boost/algorithm/string.hpp>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Effect/FontEffect.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/Font/Font.h>
#include <FalconEngine/Graphics/Renderer/Font/FontLine.h>
#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
FontRenderer::FontRenderer()
{
}

FontRenderer::~FontRenderer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
FontRenderer::Initialize(int viewportWidth, int viewportHeight)
{
    mViewportWidth  = viewportWidth;
    mViewportHeight = viewportHeight;
}

void
FontRenderer::BatchText(
    const Font *font,
    float             fontSize,
    const wstring& textString,
    Vector2f       textPosition,
    Color          textColor,
    float          textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    auto text = FontText(fontSize, textString, textPosition, textLineWidth);
    auto batch = PrepareBatch(font);
    PrepareText(*batch, font, &text, textColor);
}

// @summary Construct all the necessary lexical separation of given text into
// lines of words.
//
// @return The glyph number inside the text lines.
int
CreateTextLines(
    _IN_  const Font    *font,
    _IN_  const FontText    *text,
    _OUT_ vector<FontLine>&  lines)
{
    using namespace boost;
    static auto sLineStrings = vector<wstring>();
    sLineStrings.clear();
    split(sLineStrings, text->mTextString, is_any_of(L"\n"));

    // Bounds is formatted as [x, y, width, height]
    const auto lineWidth = text->mTextBounds[2];

    int glyphCount = 0;
    auto lineCurrent = FontLine(lineWidth);
    int lineNum = int(sLineStrings.size());
    for (int lineIndex = 0; lineIndex < lineNum; ++lineIndex)
    {
        for (const wchar_t& c : sLineStrings[lineIndex])
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
            bool success = lineCurrent.PushGlyph(glyph, fontSizeScale);
            if (!success)
            {
                // Have to start a new line for this glyph
                lines.push_back(lineCurrent);
                lineCurrent = FontLine(lineWidth);
                lineCurrent.PushGlyph(glyph, fontSizeScale);
            }
        }

        // NOTE(Wuxiang): There will be at least one line even the string is empty.
        lines.push_back(lineCurrent);
    }

    return glyphCount;
}

void
FillBufferFontAttribute(float             *textVertexBufferData,
                        size_t&            textVertexBufferDataIndex,
                        const FontGlyph *textGlyph,
                        Vector4f           textColor,
                        double fontSizeScale)
{
    // Font color
    FillBufferDataAsVector4f<float>(textVertexBufferData, textVertexBufferDataIndex, textColor);

    // NOTE(Wuxiang): 1.32 is value the when imported font size is 33. 1.32 is
    // used as origin for scaling.

    // Font width
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, 0.50 * (1 + 0.15 * (fontSizeScale - 1.32)));

    // Font edge
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, 0.03 / (1 + 1.05 * (fontSizeScale - 1.32)));

    // Font page
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mPage);
}

void
FillBufferGlyphAttribute(
    _OUT_    float             *textVertexBufferData,
    _IN_OUT_ size_t&            textVertexBufferDataIndex,
    _IN_     const FontGlyph *textGlyph,
    _IN_     Vector4f           textColor,
    _IN_     float              textGlyphX,
    _IN_     float              textGlyphY,
    _IN_     const Font  *font,
    _IN_     double             fontSizeScale)
{
    // NOTE(Wuxiang): Since x1, y1 represents left-bottom coordinate, we need to
    // process base and yoffset differently. Notably, x1 is amended to center the
    // glyph for different width, 'x + advance / 2 - width / 2' is the x1
    // considering no x offset. I don't think this cause the glyph to draw as
    // monospaced, since the advance would be different for different character
    // set, which means English would have different advance than Chinese.
    // However, the influence of width indeed is compensated using this method in
    // spacing of the glyph.
    double x1 = textGlyphX + (textGlyph->mAdvance / 2 - textGlyph->mWidth / 2 + textGlyph->mOffsetX) * fontSizeScale;
    double y2 = textGlyphY + (font->mLineBase - textGlyph->mOffsetY) * fontSizeScale;
    double y1 = y2 - textGlyph->mHeight * fontSizeScale;
    double x2 = x1 + textGlyph->mWidth * fontSizeScale;

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT1);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT2);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT2);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT1);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS2);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT2);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);

    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, x1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, y1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mS1);
    FillBufferDataAs<float, double>(textVertexBufferData, textVertexBufferDataIndex, textGlyph->mT1);
    FillBufferFontAttribute(textVertexBufferData, textVertexBufferDataIndex, textGlyph, textColor, fontSizeScale);
}

// @summary Fill the vertex buffer with the text line information.
void
FillBufferTextLines(
    _IN_  const Font    *font,
    _IN_  float                fontSize,
    _IN_  Vector2f                  textPosition,
    _IN_  Vector4f                  textColor,
    _IN_  const vector<FontLine>& textLines,
    _IN_  size_t&                   textVertexBufferDataIndex,
    _OUT_ float                    *textVertexBufferData
)
{
    float x = textPosition.x;
    float y = textPosition.y;

    double fontSizeScale = fontSize / font->mSizePt;

    for(auto& line : textLines)
    {
        for (auto& glyph : line.mLineGlyphs)
        {
            FillBufferGlyphAttribute(textVertexBufferData, textVertexBufferDataIndex, &glyph, textColor, x, y, font, fontSizeScale);

            x += float(glyph.mAdvance * fontSizeScale);
        }

        x = textPosition.x;
        y -= float(font->mLineHeight * fontSizeScale);
    }
}

void
FontRenderer::RenderBegin()
{
    for (auto& fontBatchPair : mTextBatchTable)
    {
        auto& batch = fontBatchPair.second;
        batch->mVertexBufferDataIndex = 0;
        batch->mGlyphNum = 0;
    }
}

void
FontRenderer::Render(Renderer *renderer, double /* percent */)
{
    for (auto& fontBatchPair : mTextBatchTable)
    {
        auto& batch = fontBatchPair.second;
        if (batch->mGlyphNum > 0)
        {
            // Update buffer data before drawing
            int vertexNum = batch->mGlyphNum * 6;
            batch->mVertexBuffer->SetElementNum(vertexNum);
            renderer->Update(batch->mVertexBuffer.get());
            renderer->Draw(nullptr, batch->mVertexQuads.get());
        }
    }
}

void
FontRenderer::RenderEnd()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<FontBatch>
FontRenderer::PrepareBatch(const Font *font)
{
    // When the font is prepared before.
    {
        auto iter = mTextBatchTable.find(font);
        if (iter != mTextBatchTable.end())
        {
            return iter->second;
        }
    }

    // Initialize new batch for given font.
    {
        auto fontVisualEffect = make_shared<FontEffect>();

        auto fontVertexBufferSize = int(Kilobytes(100));
        auto fontVertexBuffer = make_shared<VertexBuffer>(fontVertexBufferSize, sizeof(FontVertex), BufferUsage::Stream);

        auto fontPrimitive = make_shared<PrimitiveQuads>(fontVertexBuffer, nullptr);
        auto fontMesh = make_shared<Mesh>(fontPrimitive, nullptr);
        auto fontVisual = make_shared<Visual>(fontMesh);
        auto fontVisualEffectInstance = fontVisualEffect->CreateInstance(fontVisual.get(), font, &mTextHandedness, mViewportWidth, mViewportHeight);
        auto fontBatch = make_shared<FontBatch>(fontVertexBuffer, fontVisual);
        mTextBatchTable.insert({ font, fontBatch });
        return fontBatch;
    }
}

void
FontRenderer::PrepareText(
    _IN_OUT_ FontBatch&  batch,
    _IN_     const Font *font,
    _IN_     const FontText *text,
    _IN_     Color             textColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    static auto sTextLines = vector<FontLine>();
    sTextLines.clear();

    // Construct lines with glyph information.
    auto textGlyphCount = CreateTextLines(font, text, sTextLines);
    batch.mGlyphNum += textGlyphCount;

    // Fill the vertex attribute into the buffer
    FillBufferTextLines(font, text->mFontSize, Vector2f(text->mTextBounds.x, text->mTextBounds.y),
                        Vector4f(textColor), sTextLines, batch.mVertexBufferDataIndex,
                        reinterpret_cast<float *>(batch.mVertexBuffer->GetData()));
}


}
