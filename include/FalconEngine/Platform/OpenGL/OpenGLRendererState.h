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

// @summary Render state information to avoid redundant state changes.
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

public:
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