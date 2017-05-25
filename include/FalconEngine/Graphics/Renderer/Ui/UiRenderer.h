#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class Renderer;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#pragma warning(disable: 4251)
#if defined(FALCON_ENGINE_WINDOW_QT)
#include <QtGui/QOpenGLFunctions>
class FALCON_ENGINE_API UiRenderer final : QOpenGLFunctions
#elif defined(FALCON_ENGINE_WINDOW_GLFW)
class FALCON_ENGINE_API UiRenderer final
#endif
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    UiRenderer();
    virtual ~UiRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    void
    BatchText(const BitmapFont *font,
              float             fontSize,
              const std::wstring& textString,
              Vector2f            textPosition,
              Color               textColor = ColorPalette::White,
              float               textLineWidth = std::numeric_limits<float>().max());

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize(int width, int height);

    void
    RenderBegin();

    void
    Render(Renderer *renderer, double percent);

    void
    RenderEnd();

protected:
    BitmapFontBatchSharedPtr
    PrepareBatch(_IN_ const BitmapFont *font);

    void
    PrepareText(_IN_OUT_ BitmapFontBatch&  batch,
                _IN_     const BitmapFont *font,
                _IN_     const BitmapText *text,
                _IN_     Color             textColor = ColorPalette::White);

private:
    // NOTE(Wuxiang): Since the shader sampler could not be indexed using vertex
    // attribute input, it is impossible to use vertex attribute to do texture
    // selection. So I need to use different draw call to implement multiple font
    // support.
    // http://stackoverflow.com/questions/21524535/opengl-sampler-array-limit
    // http://stackoverflow.com/questions/12030711/glsl-array-of-textures-of-differing-size/
    using TextBatchMap = std::map<const BitmapFont *, BitmapFontBatchSharedPtr>;

    TextBatchMap          mTextBatchTable;
    HandednessRight       mTextHandedness;

    int                   mWidth  = 0; // Viewport width.
    int                   mHeight = 0; // Viewport height.
};
#pragma warning(default: 4251)

}