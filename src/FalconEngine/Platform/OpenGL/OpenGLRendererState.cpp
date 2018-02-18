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
PlatformRendererState::Initialize(const BlendState *blendState,
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
PlatformRendererState::Set(const BlendState *blendState)
{
    mBlendState.Set(blendState);
}

void
PlatformRendererState::Set(const CullState *cullState)
{
    mCullState.Set(cullState);
}

void
PlatformRendererState::Set(const DepthTestState *depthTestState)
{
    mDepthTestState.Set(depthTestState);
}

void
PlatformRendererState::Set(const OffsetState *offsetState)
{
    mOffsetState.Set(offsetState);
}

void
PlatformRendererState::Set(const StencilTestState *stencilTestState)
{
    mStencilTestState.Set(stencilTestState);
}

void
PlatformRendererState::Set(const WireframeState *wireframeState)
{
    mWireframeState.Set(wireframeState);
}

}

#endif