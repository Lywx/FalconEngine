#pragma once

#include <string>
#include <vector>
#include <limits>

#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLInclude.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLShader.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/BitmapText.h>

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

struct BitmapFontRendererContext
{
    int mWidth = 0;
    int mHeight = 0;
};

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
    Setup(BitmapFontRendererContext context);

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
    BitmapFontRendererContext           mContext;

    std::vector<BitmapFontRenderGroup>  mFontRenderGroups;
    bool                                mFontRenderGroupsDirty = false;

    PlatformShader                      mTextShaderDefault;
    std::vector<float>                  mTextShaderDefaultAttributes;
    GLuint                              mTextShaderDefaultBuffer;
    GLuint                              mTextShaderDefaultVao;

    Matrix4f                            mFontShaderCameraProjection = Matrix4f::Identity;
    PlatformShader                     *mTextShaderPrevious = nullptr;
    GLuint                              mTextShaderPreviousTexture = 0;

    std::vector<BitmapText>             mTexts;
};

}
