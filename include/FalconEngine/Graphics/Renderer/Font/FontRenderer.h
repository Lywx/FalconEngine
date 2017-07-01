#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Font/FontRenderBatch.h>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class Font;
class FontRenderBatch;
class FontText;

class Renderer;

// @summary The font renderer is the class you would call to draw a string on
// the screen.
#pragma warning(disable: 4251)
class FALCON_ENGINE_API FontRenderer final
{
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
public:
    static FontRenderer *
    GetInstance()
    {
        static FontRenderer sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    FontRenderer();

public:
    ~FontRenderer();

public:
    /************************************************************************/
    /* Rendering API                                                        */
    /************************************************************************/
    void
    BatchText(const Font *font,
              float       fontSize,

              const std::wstring& textString,
              Vector2f            textPosition,
              Color               textColor = ColorPalette::White,
              float               textLineWidth = std::numeric_limits<float>().max());

    /************************************************************************/
    /* Rendering Engine API                                                 */
    /************************************************************************/
    void
    Initialize();

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

protected:
    std::shared_ptr<FontRenderBatch>
    FindBatch(const Font *font);

    void
    FillText(_IN_     const Font      *font,
             _IN_OUT_ FontRenderBatch *batch);

private:
    // NOTE(Wuxiang): Since the shader sampler could not be indexed using vertex
    // attribute input, it is impossible to use vertex attribute to do texture
    // selection. So I need to use different draw call to implement multiple font
    // support.
    // http://stackoverflow.com/questions/21524535/opengl-sampler-array-limit
    // http://stackoverflow.com/questions/12030711/glsl-array-of-textures-of-differing-size/
    using FontRenderBatchMap = std::map<const Font *, std::shared_ptr<FontRenderBatch>>;

    FontRenderBatchMap mTextBatchTable;
};
#pragma warning(default: 4251)

}
