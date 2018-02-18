#include <FalconEngine/Platform/OpenGL/OpenGLRendererState.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>

namespace FalconEngine
{

FALCON_ENGINE_DELETER_DECLARE(PlatformRendererState, PlatformRendererStateDeleter);
FALCON_ENGINE_DELETER_IMPLEMENT(PlatformRendererState, PlatformRendererStateDeleter);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRendererState::PlatformRendererState()
{
    // Initialization must be deferred until an OpenGL context has been
    // created.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformRendererState::Initialize(Renderer *,
                                  const BlendState *blendState,
                                  const CullState *cullState,
                                  const DepthTestState *depthTestState,
                                  const OffsetState *offsetState,
                                  const StencilTestState *stencilTestState,
                                  const WireframeState *wireframeState)
{
    mBlendState.Initialize(blendState);
    mCullState.Initialize(cullState);
    mDepthTestState.Initialize(depthTestState);
    mOffsetState.Initialize(offsetState);
    mStencilTestState.Initialize(stencilTestState);
    mWireframeState.Initialize(wireframeState);
}

void
PlatformRendererState::Set(Renderer *,
                           const BlendState *blendState,
                           const CullState *cullState,
                           const DepthTestState *depthTestState,
                           const OffsetState *offsetState,
                           const StencilTestState *stencilTestState,
                           const WireframeState *wireframeState)
{
    mBlendState.Set(blendState);
    mCullState.Set(cullState);
    mDepthTestState.Set(depthTestState);
    mOffsetState.Set(offsetState);
    mStencilTestState.Set(stencilTestState);
    mWireframeState.Set(wireframeState);
}

void
PlatformRendererState::Validate(Renderer *)
{
}

}

#endif