#pragma once

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>
#include <FalconEngine/Math/Vector4f.h>

namespace FalconEngine {

class BlendState;
class CullState;
class DepthState;
class OffsetState;
class StencilState;
class WireframeState;

/// Render state information to avoid redundant state changes.
class FALCON_ENGINE_GRAPHICS_ITEM PlatformRenderState
{
public:
    PlatformRenderState();

    void Initialize(const BlendState *astate,
                    const CullState *cstate,
                    const DepthState *dstate,
                    const OffsetState *ostate,
                    const StencilState *sstate,
                    const WireframeState *wstate);

    // Blending
    bool m_BlendEnabled;
    GLenum m_BlendSource;
    GLenum m_BlendDestination;
    Vector4f m_BlendColor;

    // Culling
    bool m_CullEnabled;
    bool m_CullCW;

    // Depth Test
    bool m_DepthTestEnabled;
    bool m_DepthWriteEnabled;
    GLenum m_DepthCompareFunction;

    // OffsetState
    bool m_OffsetFillEnabled;
    bool m_OffsetLineEnabled;
    bool m_OffsetPointEnabled;
    float m_OffsetFactor;
    float m_OffsetUnit;

    // Stencil Test
    bool m_StencilTestEnabled;
    GLenum m_StencilFunction;
    GLuint m_StencilReference;
    GLuint m_StencilMask;
    GLuint m_StencilWriteMask;
    GLenum m_StencilOnStencilTestFail;
    GLenum m_StencilOnDepthTestFail;
    GLenum m_StencilOnDepthTestPass;

    // Wireframe Mode
    bool m_WireframeEnabled;
};

}