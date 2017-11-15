#pragma once

#include <FalconEngine/Core/Common.h>

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

    void
    Update(double elapsed);

    void
    UpdateFrame(double elapsed);

private:
    void
    Destroy();

public:
    DebugRenderer *
    GetDebugRenderer() const
    {
        return mDebugRenderer;
    }

    EntityRenderer *
    GetEntityRenderer() const
    {
        return mEntityRenderer;
    }

    FontRenderer *
    GetFontRenderer() const
    {
        return mFontRenderer;
    }

    Renderer *
    GetMasterRenderer() const
    {
        return mMasterRenderer;
    }

private:
    DebugRenderer      *mDebugRenderer;
    EntityRenderer     *mEntityRenderer;
    FontRenderer       *mFontRenderer;
    Renderer           *mMasterRenderer;
    UiRenderer         *mUiRenderer;
};
#pragma warning(default: 4251)

}
