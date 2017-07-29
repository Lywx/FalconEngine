#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <limits>
#include <map>
#include <string>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Font/FontResourceChannel.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferResource.h>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class Font;
class FontResourceChannel;
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
    static const int BatchItemNumMax;
    static const int FrameGlyphNumMax;

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
    AddText(const Font         *font,
            float               fontSize,
            const Vector2f&     textPosition,
            const std::string&  text,
            Color               textColor = ColorPalette::White,
            float               textLineWidth = std::numeric_limits<float>().max());

    void
    AddText(const Font         *font,
            float               fontSize,
            const Vector2f&     textPosition,
            const std::wstring& text,
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

private:
    void
    BatchText(const Font *font,
              float       fontSize,

              const std::wstring& textString,
              const Vector2f&     textPosition,
              Color               textColor = ColorPalette::White,
              float               textLineWidth = std::numeric_limits<float>().max());

    const std::shared_ptr<FontResourceChannel>&
    FindChannel(const Font *font);

    void
    FillText(_IN_     const Font          *font,
             _IN_OUT_ FontResourceChannel *fontChannelInfo);

private:
    // NOTE(Wuxiang): Since the shader sampler could not be indexed using vertex
    // attribute input, it is impossible to use vertex attribute to do texture
    // selection. So I need to use different draw call to implement multiple font
    // support.
    std::shared_ptr<BufferResource<FontResourceChannel>> mTextBufferResource;

};
#pragma warning(default: 4251)

}
