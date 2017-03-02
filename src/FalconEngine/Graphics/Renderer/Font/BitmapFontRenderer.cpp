#include <FalconEngine/Graphics/Renderer/Font/BitmapFontRenderer.h>

#include <boost/algorithm/string.hpp>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Effects/BitmapFontEffect.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualQuads.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFont.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapLine.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapText.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexBuffer.h>

using namespace std;
using namespace FalconEngine;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFontRenderer::BitmapFontRenderer()
{
}

BitmapFontRenderer::~BitmapFontRenderer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BitmapFontRenderer::Initialize(int width, int height)
{
    mWidth  = width;
    mHeight = height;
}

void
BitmapFontRenderer::BatchText(
    const BitmapFont *font,
    float             fontSize,
    const wstring& textString,
    Vector2f       textPosition,
    Color          textColor,
    float          textLineWidth)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    auto text = BitmapText(fontSize, textString, textPosition, textLineWidth);
    auto batch = PrepareBatch(font);
    PrepareText(*batch, font, &text, textColor);
}

// @summary Construct all the necessary lexical separation of given text into
// lines of words.
//
// @return The glyph number inside the text lines.
int
CreateTextLines(
    _IN_  const BitmapFont    *font,
    _IN_  const BitmapText    *text,
    _OUT_ vector<BitmapLine>&  lines)
{
    using namespace boost;
    static auto sLineStrings = vector<wstring>();
    sLineStrings.clear();
    split(sLineStrings, text->mTextString, is_any_of(L"\n"));

    // Bounds is formatted as [x, y, width, height]
    const auto lineWidth = text->mTextBounds[2];

    int glyphCount = 0;
    auto lineCurrent = BitmapLine(lineWidth);
    for (int lineIndex = 0; lineIndex < sLineStrings.size(); ++lineIndex)
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

            uint32 glyphCodepoint = c;
            auto   glyphIndex = font->mGlyphIndexTable.at(glyphCodepoint);
            auto&  glyph = font->mGlyphTable.at(glyphIndex);
            ++glyphCount;

            double fontSizeScale = text->mFontSize / font->mSizePt;
            bool success = lineCurrent.PushGlyph(glyph, fontSizeScale);
            if (!success)
            {
                // Have to start a new line for this glyph
                lines.push_back(lineCurrent);
                lineCurrent = BitmapLine(lineWidth);
                lineCurrent.PushGlyph(glyph, fontSizeScale);
            }
        }

        // NOTE(Wuxiang): There will be at least one line even the string is empty.
        lines.push_back(lineCurrent);
    }

    return glyphCount;
}

template<typename T>
inline void FillData(T *data, size_t& dataIndex, T value)
{
    data[dataIndex] = value;
    ++dataIndex;
}

// @param T is the data pointer type you need to fill in.
// @param V is the data type you provide to fill with.
template<typename T, typename V>
inline void FillDataAs(T *data, size_t& dataIndex, V value)
{
    FillData<T>(data, dataIndex, T(value));
}

void
FillFontAttribute(float              *textData,
                  size_t&            textDataIndex,
                  const BitmapGlyph *textGlyph,
                  Vector4f           textColor,
                  double fontSizeScale)
{
    // Font color
    FillDataAs<float, double>(textData, textDataIndex, textColor.x);
    FillDataAs<float, double>(textData, textDataIndex, textColor.y);
    FillDataAs<float, double>(textData, textDataIndex, textColor.z);
    FillDataAs<float, double>(textData, textDataIndex, textColor.w);

    // NOTE(Wuxiang): 1.32 is value the when imported font size is 33. 1.32 is
    // used as origin for scaling.

    // Font width
    FillDataAs<float, double>(textData, textDataIndex, 0.50 * (1 + 0.15 * (fontSizeScale - 1.32)));

    // Font edge
    FillDataAs<float, double>(textData, textDataIndex, 0.03 / (1 + 1.05 * (fontSizeScale - 1.32)));

    // Font page
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mPage);
}

void
FillGlyphAttribute(
    _OUT_    float              *textData,
    _IN_OUT_ size_t&            textDataIndex,
    _IN_     const BitmapGlyph *textGlyph,
    _IN_     Vector4f           textColor,
    _IN_     float              textGlyphX,
    _IN_     float              textGlyphY,
    _IN_     const BitmapFont *font,
    _IN_     double            fontSizeScale)
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

    FillDataAs<float, double>(textData, textDataIndex, x1);
    FillDataAs<float, double>(textData, textDataIndex, y1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT1);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);

    FillDataAs<float, double>(textData, textDataIndex, x2);
    FillDataAs<float, double>(textData, textDataIndex, y2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT2);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);

    FillDataAs<float, double>(textData, textDataIndex, x1);
    FillDataAs<float, double>(textData, textDataIndex, y2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT2);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);

    FillDataAs<float, double>(textData, textDataIndex, x2);
    FillDataAs<float, double>(textData, textDataIndex, y1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT1);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);

    FillDataAs<float, double>(textData, textDataIndex, x2);
    FillDataAs<float, double>(textData, textDataIndex, y2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS2);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT2);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);

    FillDataAs<float, double>(textData, textDataIndex, x1);
    FillDataAs<float, double>(textData, textDataIndex, y1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mS1);
    FillDataAs<float, double>(textData, textDataIndex, textGlyph->mT1);
    FillFontAttribute(textData, textDataIndex, textGlyph, textColor, fontSizeScale);
}

// @summary Fill the vertex buffer with the text line information.
void
FillTextLines(
    _IN_  const BitmapFont    *font,
    _IN_  float               fontSize,
    _IN_  Vector2f                  textPosition,
    _IN_  Vector4f                  textColor,
    _IN_  const vector<BitmapLine>& textLines,
    _IN_  size_t&                   textDataIndex,
    _OUT_ float                     *textData
)
{
    float x = textPosition.x;
    float y = textPosition.y;

    double fontSizeScale = fontSize / font->mSizePt;

    for(auto& line : textLines)
    {
        for (auto& glyph : line.mLineGlyphs)
        {
            FillGlyphAttribute(textData, textDataIndex, &glyph, textColor, x, y, font, fontSizeScale);

            x += float(glyph.mAdvance * fontSizeScale);
        }

        x = textPosition.x;
        y -= float(font->mLineHeight * fontSizeScale);
    }
}

void
BitmapFontRenderer::RenderBegin()
{
    for (auto& batchPair : mTextBatchTable)
    {
        auto& batch = batchPair.second;
        batch->mBufferDataIndex = 0;
        batch->mBufferGlyphNum = 0;
    }
}

void
BitmapFontRenderer::Render(Renderer *renderer, double percent)
{
    for (auto& batchPair : mTextBatchTable)
    {
        auto& batch = batchPair.second;
        if (batch->mBufferGlyphNum > 0)
        {
            // Update buffer data before drawing
            batch->mBuffer->SetElementNum(batch->mBufferGlyphNum * 6);
            renderer->Update(batch->mBuffer.get());
            renderer->Draw(batch->mQuads.get());
        }
    }
}

void
BitmapFontRenderer::RenderEnd()
{
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
BitmapFontBatchSharedPtr
BitmapFontRenderer::PrepareBatch(const BitmapFont *font)
{
    // When the font is prepared before.
    auto iter = mTextBatchTable.find(font);
    if (iter != mTextBatchTable.end())
    {
        return iter->second;
    }

    static const size_t                 sFontBufferSize = Kilobytes(10);
    static VertexFormatSharedPtr        sFontBufferVertexFormat;
    static shared_ptr<BitmapFontEffect> sFontEffect;

    if (sFontEffect == nullptr)
    {
        sFontEffect = make_shared<BitmapFontEffect>(&mTextHandedness);
    }

    if (sFontBufferVertexFormat == nullptr)
    {
        sFontBufferVertexFormat = sFontEffect->CreateVertexFormat();
    }

    auto fontBuffer = make_shared<VertexBuffer>(sFontBufferSize, sizeof(BitmapFontVertex), BufferUsage::Dynamic);

    // Setup font specific visual quad.
    shared_ptr<VisualQuads> fontQuads;
    {
        auto vertexGroup = make_shared<VertexGroup>();
        vertexGroup->SetVertexBuffer(0, fontBuffer, 0, sFontBufferVertexFormat->GetVertexAttributeStride());

        auto fontEffectInstance = make_shared<VisualEffectInstance>(sFontEffect);
        sFontEffect->CreateInstance(fontEffectInstance.get(), font, mWidth, mHeight);

        fontQuads = make_shared<VisualQuads>(sFontBufferVertexFormat, vertexGroup);
        fontQuads->SetEffectInstance(fontEffectInstance);
    }

    auto fontBatch = make_shared<BitmapFontBatch>(fontBuffer, fontQuads);
    mTextBatchTable.insert({ font, fontBatch });
    return fontBatch;
}

void
BitmapFontRenderer::PrepareText(
    _IN_OUT_ BitmapFontBatch&  batch,
    _IN_     const BitmapFont *font,
    _IN_     const BitmapText *text,
    _IN_     Color             textColor)
{
    FALCON_ENGINE_CHECK_NULLPTR(font);

    static auto sTextLines = vector<BitmapLine>();
    sTextLines.clear();

    // Construct lines with glyph information.
    int textGlyphCount = CreateTextLines(font, text, sTextLines);
    batch.mBufferGlyphNum += textGlyphCount;

    // Fill the vertex attribute into the buffer
    FillTextLines(font, text->mFontSize, Vector2f(text->mTextBounds.x, text->mTextBounds.y),
                  Vector4f(textColor), sTextLines, batch.mBufferDataIndex,
                  reinterpret_cast<float *>(batch.mBuffer->GetData()));
}


}
