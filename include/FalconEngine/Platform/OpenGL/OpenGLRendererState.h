#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Platform/OpenGL/OpenGLBlendState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLCullState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLDepthTestState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLOffsetState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLStencilTestState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLWireframeState.h>

namespace FalconEngine
{

class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

// NOTE(Wuxiang): if you later decide to add drawcall sorting based on the
// renderer state, this is the place you would track a list of drawcall
// renderer state description. The current code doesn't do draw command sorting.

// @summary Render state information to avoid redundant state changes.
// @remark Basically, all the draw call's state should be tracked here.
FALCON_ENGINE_CLASS_BEGIN PlatformRendererState
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    PlatformRendererState();
    ~PlatformRendererState() = default;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize(const BlendState * blendState,
               const CullState * cullState,
               const DepthTestState * depthTestState,
               const OffsetState * offsetState,
               const StencilTestState * stencilTestState,
               const WireframeState * wireframeState);

    void
    Set(const BlendState * blendState);

    void
    Set(const CullState * cullState);

    void
    Set(const DepthTestState * depthTestState);

    void
    Set(const OffsetState * offsetState);

    void
    Set(const StencilTestState * stencilTestState);

    void
    Set(const WireframeState * wireframeState);

private:
    PlatformBlendState mBlendState;
    PlatformCullState mCullState;
    PlatformDepthTestState mDepthTestState;
    PlatformOffsetState mOffsetState;
    PlatformStencilTestState mStencilTestState;
    PlatformWireframeState mWireframeState;
};
FALCON_ENGINE_CLASS_END

}

#endif