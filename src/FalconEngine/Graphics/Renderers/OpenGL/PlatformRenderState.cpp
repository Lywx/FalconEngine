#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformRenderState.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformExtensions.h>

#include <FalconEngine/Graphics/States/BlendState.h>
#include <FalconEngine/Graphics/States/CullState.h>
#include <FalconEngine/Graphics/States/DepthState.h>
#include <FalconEngine/Graphics/States/OffsetState.h>
#include <FalconEngine/Graphics/States/StencilState.h>
#include <FalconEngine/Graphics/States/WireframeState.h>

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformRenderState::PlatformRenderState()
{
    // Initialization must be deferred until an OpenGL context has been
    // created.
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void PlatformRenderState::Initialize(const BlendState *blending,
                                     const CullState *cull,
                                     const DepthState *depth,
                                     const OffsetState *offset,
                                     const StencilState *stencil,
                                     const WireframeState *wireframe)
{
    // Blending
    m_BlendEnabled = blending->BlendEnabled;
    m_BlendSource = OpenGLBlendFactorSource[int(blending->BlendSourceFactor)];
    m_BlendDestination = OpenGLBlendFactorDestination[int(blending->BlendDestinationFactor)];
    m_BlendColor = blending->BlendConstantFactor;

    m_BlendEnabled ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
    glBlendFunc(m_BlendSource, m_BlendDestination);
    glBlendColor(m_BlendColor[0], m_BlendColor[1], m_BlendColor[2],
                 m_BlendColor[3]);

    // Culling
    m_CullEnabled = cull->CullEnabled;
    m_CullCW = cull->CullCW;

    m_CullEnabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(m_CullCW ? GL_BACK : GL_FRONT);

    // Depth Test
    m_DepthTestEnabled = depth->DepthTestEnabled;
    m_DepthWriteEnabled = depth->DepthWriteEnabled;
    m_DepthCompareFunction = OpenGLDepthCompareFunction[int(depth->DepthCompareFunction)];

    m_DepthTestEnabled ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

    // You still need to have to enable depth test to enable writing to depth buffer
    glDepthMask(m_DepthWriteEnabled ? GL_TRUE : GL_FALSE);
    glDepthFunc(m_DepthCompareFunction);

    // Offset State
    m_OffsetFillEnabled = offset->OffsetFillEnabled;
    m_OffsetLineEnabled = offset->OffsetLineEnabled;
    m_OffsetPointEnabled = offset->OffsetPointEnabled;
    m_OffsetFactor = offset->OffsetFactor;
    m_OffsetUnit = offset->OffsetUnit;

    m_OffsetFillEnabled ? glEnable(GL_POLYGON_OFFSET_FILL) : glDisable(GL_POLYGON_OFFSET_FILL);
    m_OffsetLineEnabled ? glEnable(GL_POLYGON_OFFSET_LINE) : glDisable(GL_POLYGON_OFFSET_LINE);
    m_OffsetPointEnabled ? glEnable(GL_POLYGON_OFFSET_POINT) : glDisable(GL_POLYGON_OFFSET_POINT);
    glPolygonOffset(m_OffsetFactor, m_OffsetUnit);

    // Stencil Test
    m_StencilTestEnabled = stencil->StencilTestEnabled;
    m_StencilFunction = OpenGLStencilFunction[int(stencil->StencilFunction)];
    m_StencilReference = stencil->StencilReference;
    m_StencilMask = stencil->StencilMask;
    m_StencilWriteMask = stencil->StencilWriteMask;
    m_StencilOnStencilTestFail = OpenGLStencilOperation[int(stencil->OnStencilTestFail)];
    m_StencilOnDepthTestFail = OpenGLStencilOperation[int(stencil->OnDepthTestFail)];
    m_StencilOnDepthTestPass = OpenGLStencilOperation[int(stencil->OnDepthTestPass)];

    m_StencilTestEnabled ? glEnable(GL_STENCIL_TEST) : glDisable(GL_STENCIL_TEST);
    glStencilFunc(m_StencilFunction, m_StencilReference, m_StencilMask);
    glStencilMask(m_StencilWriteMask);
    glStencilOp(m_StencilOnStencilTestFail, m_StencilOnDepthTestFail, m_StencilOnDepthTestPass);

    // Wireframe Mode
    m_WireframeEnabled = wireframe->Enabled;

    glPolygonMode(GL_FRONT_AND_BACK, m_WireframeEnabled ? GL_LINE : GL_FILL);
}

}