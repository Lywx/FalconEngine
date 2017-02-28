#pragma once

#include <FalconEngine/Context/ContextInclude.h>

#include <limits>

#include <FalconEngine/Context/GameEngineGraphicsSettings.h>
#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderers/Renderer.h>
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

class GameEngineData;
class GameEngineGraphics
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEngineGraphics *
    GetInstance()
    {
        static GameEngineGraphics sInstance;
        return &sInstance;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineGraphics();
    ~GameEngineGraphics();

public:
    /************************************************************************/
    /* Renderer API                                                         */
    /************************************************************************/
    void
    ClearColorBuffer(Vector4f color)
    {
        mRenderer->ClearColorBuffer(color);
    }

    void
    ClearDepthBuffer(float depth)
    {
        mRenderer->ClearDepthBuffer(depth);
    }

    void
    ClearStencilBuffer(unsigned int stencil)
    {
        mRenderer->ClearDepthBuffer(stencil);
    }

    void
    ClearBuffers(Vector4f color, float depth, unsigned int stencil)
    {
        mRenderer->ClearBuffers(color, depth, stencil);
    }

    void
    DrawStaticString(const BitmapFont *font,
                     float             fontSize,
                     Vector2f           textPosition,
                     const std::string& text,
                     const Color        textColor = ColorPalette::White,
                     float              textLineWidth = std::numeric_limits<float>().max());

    void
    DrawString(const BitmapFont *font,
               float             fontSize,
               Vector2f           textPosition,
               const std::string& text,
               const Color        textColor = ColorPalette::White,
               float              textLineWidth = std::numeric_limits<float>().max());

public:
    void
    Initialize(
        _IN_  const GameEngineData       *data,
        _OUT_ GameEngineSettingsSharedPtr settings);

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

private:
    void
    InitializePlatform(const GameEngineData *data);

    void
    Destroy();

protected:
    BitmapFontRenderer                 *mRendererForFont;
    Renderer                           *mRenderer;
    GameEngineGraphicsSettingsSharedPtr mSettings;
};

}
