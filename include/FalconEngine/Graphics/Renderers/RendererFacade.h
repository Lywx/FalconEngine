#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <limits>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

/************************************************************************/
/* Specialized Renderer                                                 */
/************************************************************************/
class BitmapFont;
class BitmapFontRenderer;
class BitmapText;

/************************************************************************/
/* General Renderer                                                     */
/************************************************************************/
class Renderer;
class RendererFacade
{
public:
    RendererFacade();
    ~RendererFacade();

public:
    void
    DrawString(BitmapFont *font,
               float       fontSize,
               Vector2f          textPosition,
               const BitmapText *text,
               const Color       textColor = ColorPalette::White,
               float             textLineWidth = std::numeric_limits<float>().max());

    void
    DrawString(BitmapFont *font,
               float       fontSize,
               Vector2f           textPosition,
               const std::string& text,
               const Color        textColor = ColorPalette::White,
               float              textLineWidth = std::numeric_limits<float>().max());

public:
    void
    Initialize(int width, int height);

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

protected:
    BitmapFontRenderer *mRendererForFont;
    Renderer           *mRenderer;
};

}
