#pragma once

#include <FalconEngine/Context/Common.h>

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
class DebugRenderer;

class Font;
class FontRenderer;
class FontText;

class Camera;

class Entity;
class EntityRenderer;

class UiRenderer;

/************************************************************************/
/* General Renderer                                                     */
/************************************************************************/
class Renderer;

class GameEngineData;
class GameEngineSettings;

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

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineGraphics();

public:
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
    DrawString(const Font   *font,
               float               fontSize,
               Vector2f            textPosition,
               const std::string&  text,
               Color               textColor = ColorPalette::White,
               float               textLineWidth = std::numeric_limits<float>().max());

    void
    DrawString(const Font   *font,
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
    Initialize();

    void
    RenderBegin();

    void
    Render(double percent);

    void
    RenderEnd();

    void
    Update(double elapsed);

private:
    void
    Destroy();

private:
    DebugRenderer      *mDebugRenderer;
    EntityRenderer     *mEntityRenderer;
    FontRenderer       *mFontRenderer;
    Renderer           *mMasterRenderer;
    UiRenderer         *mUiRenderer;
};
#pragma warning(default: 4251)

}
