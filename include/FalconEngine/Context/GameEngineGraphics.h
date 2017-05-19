#pragma once

#include <FalconEngine/Context/Header.h>

#include <limits>

#include <FalconEngine/Graphics/Renderer/Viewport.h>
#include <FalconEngine/Graphics/Renderer/Window.h>

#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector4.h>

namespace FalconEngine
{

/************************************************************************/
/* Specialized Renderer                                                 */
/************************************************************************/
class BitmapFont;
class BitmapFontRenderer;
using BitmapFontRendererSharedPtr = std::shared_ptr<BitmapFontRenderer>;
class BitmapText;

class Camera;
class Entity;
class EntityRenderer;
using EntityRendererSharedPtr = std::shared_ptr<EntityRenderer>;

/************************************************************************/
/* General Renderer                                                     */
/************************************************************************/
class Renderer;
using RendererSharedPtr = std::shared_ptr<Renderer>;

class GameEngineSettings;
using GameEngineSettingsSharedPtr = std::shared_ptr<GameEngineSettings>;

class GameEngineData;
using GameEngineDataSharedPtr = std::shared_ptr<GameEngineData>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineGraphics
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
    /* Rendering API                                                        */
    /************************************************************************/
    void
    ClearColorBuffer(Vector4f color);

    void
    ClearDepthBuffer(float depth);

    void
    ClearFrameBuffer(Vector4f color, float depth, unsigned int stencil);

    void
    ClearStencilBuffer(unsigned int stencil);

    void
    Draw(const Camera *camera, const Entity *entity);

    void
    DrawBoundingBox(const Camera *camera,
                    const Entity *entity,
                    Color         color = Transparent(ColorPalette::White, 0.5f));

    void
    DrawString(const BitmapFont   *font,
               float               fontSize,
               Vector2f            textPosition,
               const std::string&  text,
               Color               textColor = ColorPalette::White,
               float               textLineWidth = std::numeric_limits<float>().max());

    void
    DrawString(const BitmapFont   *font,
               float               fontSize,
               Vector2f            textPosition,
               const std::wstring& text,
               Color               textColor = ColorPalette::White,
               float               textLineWidth = std::numeric_limits<float>().max());

    const Viewport *
    GetViewport() const;

    void
    SetViewport(float x, float y, float width, float height);

    const Window *
    GetWindow() const;

    void
    SetWindow(int width, int height, float near, float far);

public:
    void
    Initialize(
        _IN_ GameEngineDataSharedPtr     gameEngineData,
        _IN_ GameEngineSettingsSharedPtr gameEngineSettings);

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

private:
    void
    Destroy();

protected:
    EntityRendererSharedPtr     mEntityRenderer;
    BitmapFontRendererSharedPtr mFontRenderer;
    RendererSharedPtr           mMasterRenderer;

    GameEngineSettingsSharedPtr mGameEngineSettings;
};
#pragma warning(default: 4251)

}
