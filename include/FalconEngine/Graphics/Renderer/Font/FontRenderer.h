#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Font/FontBatch.h>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class Font;
class FontBatch;
class FontText;

class Renderer;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#pragma warning(disable: 4251)
#if defined(FALCON_ENGINE_WINDOW_QT)
#include <QtGui/QOpenGLFunctions>
class FALCON_ENGINE_API FontRenderer final : QOpenGLFunctions
#elif defined(FALCON_ENGINE_WINDOW_GLFW)
class FALCON_ENGINE_API FontRenderer final
#endif
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    FontRenderer();
    virtual ~FontRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    void
    BatchText(const Font *font,
              float             fontSize,
              const std::wstring& textString,
              Vector2f            textPosition,
              Color               textColor = ColorPalette::White,
              float               textLineWidth = std::numeric_limits<float>().max());

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize(int viewportWidth, int viewportHeight);

    void
    RenderBegin();

    void
    Render(Renderer *renderer, double percent);

    void
    RenderEnd();

protected:
    std::shared_ptr<FontBatch>
    PrepareBatch(_IN_ const Font *font);

    void
    PrepareText(_IN_OUT_ FontBatch&  batch,
                _IN_     const Font *font,
                _IN_     const FontText *text,
                _IN_     Color             textColor = ColorPalette::White);

private:
    // NOTE(Wuxiang): Since the shader sampler could not be indexed using vertex
    // attribute input, it is impossible to use vertex attribute to do texture
    // selection. So I need to use different draw call to implement multiple font
    // support.
    // http://stackoverflow.com/questions/21524535/opengl-sampler-array-limit
    // http://stackoverflow.com/questions/12030711/glsl-array-of-textures-of-differing-size/
    using TextBatchMap = std::map<const Font *, std::shared_ptr<FontBatch>>;

    TextBatchMap          mTextBatchTable;
    HandednessRight       mTextHandedness;

    int                   mViewportWidth  = 0;
    int                   mViewportHeight = 0;
};
#pragma warning(default: 4251)

}
