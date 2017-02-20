#pragma once

#include <string>
#include <vector>
#include <limits>

#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/BitmapText.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>

// TODO(Wuxiang 2016-12-29 22:27): Integrate the font renderer with current renderer.
namespace FalconEngine
{

// @summary Represent a font rendering instance.
struct BitmapFontRenderGroup
{
    BitmapFont         *mFont;
    Shader             *mTextShader;
    std::vector<float> *mTextShaderAttributes;
    GLuint              mTextShaderBuffer;
    size_t              mTextVertexCount;
    GLuint              mTextShaderVao;
};

class BitmapFontEffect;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#if defined(EMBTI_QT_EMBEDDING)
#include <QtGui/QOpenGLFunctions>
class BitmapFontRenderer : QOpenGLFunctions
#else
class BitmapFontRenderer
#endif
{
public:
    BitmapFontRenderer();
    ~BitmapFontRenderer();

    void
    Initialize(int width, int height);

    void
    DrawText(BitmapFont&  font,
             float        fontSize,
             std::string  textString,
             Vector2f     textPosition,
             float        textLineWidth = std::numeric_limits<float>().max(),
             Color        textColor = ColorPalette::White);

    void
    PrepareString(BitmapFont *font,
                  Shader     *textShader,
                  BitmapText *text,
                  Color       textColor = ColorPalette::White);

    void RenderBegin();
    void Render();
    void RenderEnd();

private:
    std::vector<BitmapFontRenderGroup> mTextBatch;
    bool                               mTextBatchDirty = false;

    VertexBufferSharedPtr              mTextBufferDynamic;
    VertexBufferSharedPtr              mTextBufferStream;

    BitmapFontEffect                  *mTextEffect;
    VisualEffectInstanceSharedPtr      mTextEffectInstance;
};

}
