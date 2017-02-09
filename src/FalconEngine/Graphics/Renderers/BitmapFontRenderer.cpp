#include <FalconEngine/Graphics/Renderers/BitmapFontRenderer.h>

#include <algorithm>
#include <numeric>

#include <boost/algorithm/string.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/gtc/type_ptr.hpp>

#include <FalconEngine/Graphics/Renderers/BitmapLine.h>

using namespace std;
using namespace boost;
using namespace FalconEngine;

namespace FalconEngine
{

BitmapFontRenderer::BitmapFontRenderer()
{
}

BitmapFontRenderer::~BitmapFontRenderer()
{
}

void
BitmapFontRenderer::Setup(BitmapFontRendererContext context)
{
    mContext = context;

    // Load font shader
    mTextShaderDefault.CreateFromFile(GL_VERTEX_SHADER,   "Content/Shaders/Font.vert.glsl");
    mTextShaderDefault.CreateFromFile(GL_FRAGMENT_SHADER, "Content/Shaders/Font.frag.glsl");
    mTextShaderDefault.LinkProgram();

    mTextShaderDefault.Enable();

    mTextShaderDefault.DeclareAttribute("VertexCoord");
    mTextShaderDefault.DeclareAttribute("TextureCoord");
    mTextShaderDefault.DeclareAttribute("FontColor");
    mTextShaderDefault.DeclareAttribute("FontWidth");
    mTextShaderDefault.DeclareAttribute("FontEdge");
    mTextShaderDefault.DeclareAttribute("FontPage");

    mTextShaderDefault.DeclareUniform("Projection");
    mTextShaderDefault.DeclareUniform("Texture");

    mFontShaderCameraProjection = glm::ortho(0.0f, float(mContext.mWidth), 0.0f, float(mContext.mHeight));
    glUniformMatrix4fv(mTextShaderDefault["Projection"], 1, GL_FALSE, value_ptr(mFontShaderCameraProjection[0]));
    mTextShaderDefault.Disable();

    // Prepare text batcher and text buffer
    glGenVertexArrays(1, &mTextShaderDefaultVao);
    glBindVertexArray(mTextShaderDefaultVao);

    glGenBuffers(1, &mTextShaderDefaultBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mTextShaderDefaultBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, mTextShaderDefaultBuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 0 * sizeof(float)));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 2 * sizeof(float)));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 4 * sizeof(float)));
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 8 * sizeof(float)));
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET( 9 * sizeof(float)));
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), BUFFER_OFFSET(10 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void BitmapFontRenderer::DrawText(
    BitmapFont& font,
    float       fontSize,
    string  textString,
    Vector2f textPosition,
    float    textLineWidth,
    Color    textColor)
{
    mTexts.push_back(BitmapText(fontSize, textString, textPosition, textLineWidth));
    PrepareText(font, mTextShaderDefault, mTexts.back(), textColor);
}

// @summary Construct all the necessary lexical separation of given text into
// lines of words.
//
// @return The glyph number inside the text lines.
int
CreateLines(
    IN  const BitmapFont   *font,
    IN  BitmapText         *text,
    OUT vector<BitmapLine>& lines)
{
    static auto lineStrings = vector<string>();
    lineStrings.clear();
    split(lineStrings, text->mTextString, is_any_of("\n"));

    // Bounds is formatted as [x, y, width, height]
    const auto lineWidth = text->mTextBounds[2];

    int glyphCount = 0;
    auto lineCurrent = BitmapLine(lineWidth);
    for (int lineIndex = 0; lineIndex < lineStrings.size(); ++lineIndex)
    {
        for (const wchar_t& c : lineStrings[lineIndex])
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

void PushGlyphFontAttribute(
    vector<float>& textAttributes, BitmapGlyph& textGlyph, Vector4f textColor, double fontSizeScale)
{
    // font color
    textAttributes.push_back(textColor.x);
    textAttributes.push_back(textColor.y);
    textAttributes.push_back(textColor.z);
    textAttributes.push_back(textColor.w);

    // NOTE(Wuxiang): 1.32 is value the when imported font size is 33. 1.32 is
    // used as origin for scaling.

    // font width
    textAttributes.push_back(0.50f * (1 + 0.15 * (fontSizeScale - 1.32)));

    // font edge
    textAttributes.push_back(0.03f / (1 + 1.05 * (fontSizeScale - 1.32)));

    // font page
    textAttributes.push_back(textGlyph.mPage);
}

void PushGlyphAttribute(vector<float>& textAttributes,
                        BitmapGlyph& textGlyph,
                        Vector4f textColor,
                        float textGlyphX, float textGlyphY,
                        BitmapFont& font, double fontSizeScale)
{
    // NOTE(Wuxiang): Since x1, y1 represents left-bottom coordinate, we need to
    // process base and yoffset differently. Notably, x1 is amended to center the
    // glyph for different width, 'x + advance / 2 - width / 2' is the x1
    // considering no x offset. I don't think this cause the glyph to draw as
    // monospaced, since the advance would be different for different character
    // set, which means English would have different advance than Chinese.
    // However, the influence of width indeed is compensated using this method in
    // spacing of the glyph.
    double x1 = textGlyphX + (textGlyph.mAdvance / 2 - textGlyph.mWidth / 2 + textGlyph.mOffsetX) * fontSizeScale;
    double y2 = textGlyphY + (font.mLineBase - textGlyph.mOffsetY) * fontSizeScale;
    double y1 = y2 - textGlyph.mHeight * fontSizeScale;
    double x2 = x1 + textGlyph.mWidth * fontSizeScale;

    textAttributes.push_back(x1);
    textAttributes.push_back(y1);
    textAttributes.push_back(textGlyph.mS1);
    textAttributes.push_back(textGlyph.mT1);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);

    textAttributes.push_back(x2);
    textAttributes.push_back(y2);
    textAttributes.push_back(textGlyph.mS2);
    textAttributes.push_back(textGlyph.mT2);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);

    textAttributes.push_back(x1);
    textAttributes.push_back(y2);
    textAttributes.push_back(textGlyph.mS1);
    textAttributes.push_back(textGlyph.mT2);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);

    textAttributes.push_back(x2);
    textAttributes.push_back(y1);
    textAttributes.push_back(textGlyph.mS2);
    textAttributes.push_back(textGlyph.mT1);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);

    textAttributes.push_back(x2);
    textAttributes.push_back(y2);
    textAttributes.push_back(textGlyph.mS2);
    textAttributes.push_back(textGlyph.mT2);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);

    textAttributes.push_back(x1);
    textAttributes.push_back(y1);
    textAttributes.push_back(textGlyph.mS1);
    textAttributes.push_back(textGlyph.mT1);
    PushGlyphFontAttribute(textAttributes, textGlyph, textColor, fontSizeScale);
}

void
CreateAttributes(
    IN const BitmapFont   *font,
    IN float               fontSize,
    IN Vector2f                  textPosition,
    IN Vector4f                  textColor,
    IN const vector<BitmapLine>& textLines,
    OUT vector<float>&           textAttributes)
{
    float x = textPosition.x;
    float y = textPosition.y;

    double fontSizeScale = fontSize / font->mSizePt;

    for(auto& line : textLines)
    {
        for (auto& glyph : line.mLineGlyphs)
        {
            PushGlyphAttribute(textAttributes, glyph, textColor, x, y, font, fontSizeScale);

            x += glyph.mAdvance * fontSizeScale;
        }

        x = textPosition.x;
        y -= font->mLineHeight * fontSizeScale;
    }
}

void
BitmapFontRenderer::PrepareString(
    const BitmapFont *font,
    Shader     *textShader,
    BitmapText *text,
    Color       textColor)
{
    static auto textLines = vector<BitmapLine>();
    textLines.clear();

    int textGlyphCount = CreateLines(font, text, textLines);

    // TODO(Wuxiang): Add multiple font and shader support. Replace the default with shader specific attribute vector.
    // Fill the vertex attribute into the buffer
    CreateAttributes(font, text.mFontSize, Vector2f(text.mTextBounds.x, text.mTextBounds.y), Vector4f(textColor), textLines, mTextShaderDefaultAttributes);

    // Find the render group this group of text belongs to.
    int  renderGroupIndex;
    bool renderGroupFound = false;
    for (renderGroupIndex = 0; renderGroupIndex < mFontRenderGroups.size(); ++renderGroupIndex)
    {
        if (mFontRenderGroups[renderGroupIndex].mFont == &font
                && mFontRenderGroups[renderGroupIndex].mTextShader == &textShader)
        {
            renderGroupFound = true;
            break;
        }
    }

    if (renderGroupFound)
    {
        mFontRenderGroups[renderGroupIndex].mTextVertexCount += textGlyphCount * 6;
    }
    else
    {
        // TODO(Wuxiang): Add multiple font and shader support. Replace the default attributes, buffer, vao with shader specific ones.
        BitmapFontRenderGroup renderGroup;
        renderGroup.mFont = &font;
        renderGroup.mTextShader = &textShader;
        renderGroup.mTextShaderAttributes = &mTextShaderDefaultAttributes;
        renderGroup.mTextShaderBuffer = mTextShaderDefaultBuffer;
        renderGroup.mTextShaderVao = mTextShaderDefaultVao;
        renderGroup.mTextVertexCount = textGlyphCount * 6;
        mFontRenderGroups.push_back(renderGroup);
    }

    mFontRenderGroupsDirty = true;
}

void BitmapFontRenderer::PrepareText(
    BitmapFont& font,
    Shader&     textShader,
    BitmapText& text,
    Color       textColor)
{
}

void BitmapFontRenderer::RenderBegin()
{
    // Switch GL State
    auto a = DepthTestState();
    a.mTestEnabled = true;
    mRenderer->SetDepthState(a);

    auto b = BlendState();
    b.mEnabled = true;
    b.mSourceFactor = BlendSourceFactor::SRC_ALPHA;
    b.mDestinationFactor = BlendDestinationFactor::ONE_MINUS_SRC_ALPHA;
    mRenderer->SetBlendState(b);

    if (mTextShaderPrevious != nullptr)
    {
        mTextShaderPrevious->Enable();
    }

    // Sort render groups when necessary
    if (mFontRenderGroupsDirty)
    {
        // NOTE(Wuxiang): According to these refs, shader switch is more expensive
        // than texture binding:
        // 1. http://stackoverflow.com/questions/29623892/cost-of-opengl-state-vb-ib-texture-changes
        // 2. Cass Everitt, John McDonald Beyond Porting_ How Modern OpenGL Can
        // Radically Reduce Driver Overhead, 2014, P48
        //
        // So that result should be like: (s1, t1), (s1, t2), (s2, t1), (s2, t2),
        // where s stands for shader and t stands for texture object. You need to
        // switch texture object for different font.
        std::stable_sort(mFontRenderGroups.begin(), mFontRenderGroups.end(),
                         [](BitmapFontRenderGroup lhs, BitmapFontRenderGroup rhs) -> bool
        {
            return lhs.mFont->mName < rhs.mFont->mName;
        });

        std::stable_sort(mFontRenderGroups.begin(), mFontRenderGroups.end(),
                         [](BitmapFontRenderGroup lhs, BitmapFontRenderGroup rhs) -> bool
        {
            return lhs.mTextShader->GetProgram() < rhs.mTextShader->GetProgram();
        });

        mFontRenderGroupsDirty = false;
    }
}

void BitmapFontRenderer::Render()
{
    for (auto renderGroup : mFontRenderGroups)
    {
        GLuint renderGroupTexture = renderGroup.mFont->mTextureObject;
        Shader& renderGroupShader = *renderGroup.mTextShader;
        GLuint renderGroupVao = renderGroup.mTextShaderVao;
        GLuint renderGroupBuffer = renderGroup.mTextShaderBuffer;
        vector<float>& renderGroupAttributes = *renderGroup.mTextShaderAttributes;

        // Switch shader program
        if (mTextShaderPrevious == nullptr || renderGroupShader.GetProgram() != mTextShaderPrevious->GetProgram())
        {
            // NOTE(Wuxiang): We could use this because Disable would reset the
            // shader program globally.
            renderGroupShader.Disable();
            renderGroupShader.Enable();

            mTextShaderPrevious = &renderGroupShader;
        }

        // Switch shader texture
        if (renderGroupTexture != mTextShaderPreviousTexture)
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D_ARRAY, renderGroupTexture);

            mTextShaderPreviousTexture = renderGroupTexture;
        }

        glBindVertexArray(renderGroupVao);

        // NOTE(Wuxiang): Use orphaning strategy
        // TODO(Wuxiang): Wrong. Use glMapBuffer to access asynchronously
        glBindBuffer(GL_ARRAY_BUFFER, renderGroupBuffer);
        glBufferData(GL_ARRAY_BUFFER, renderGroupAttributes.size() * sizeof(float), nullptr, GL_STREAM_DRAW);
        auto *va = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

        // TODO(Move this to data creation?)
        va copy &renderGroupAttributes[0];
        glUnmapBuffer(GL_ARRAY_BUFFER);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);
        glEnableVertexAttribArray(5);

        glUniform1i(renderGroupShader["Texture"], 0);

        glDrawArrays(GL_TRIANGLES, 0, renderGroup.mTextVertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);
        glDisableVertexAttribArray(5);

        glBindVertexArray(0);
    }
}

void BitmapFontRenderer::RenderEnd()
{
    mFontRenderGroups.clear();
    mTextShaderPrevious->Disable();
    mTexts.clear();
    mTextShaderDefaultAttributes.clear();
}

}
