#include <FalconEngine/Graphics/Renderers/Renderer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformRenderState.h>

namespace FalconEngine {

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

// TODO
//void Renderer::SetBlendState(const BlendState *alphaState)
//{
//    if (!mOverrideAlphaState)
//    {
//        m_renderState. = alphaState;
//    }
//    else
//    {
//        mAlphaState = mOverrideAlphaState;
//    }
//
//    if (mAlphaState->BlendEnabled)
//    {
//        if (!mData->mCurrentRS.mAlphaBlendEnabled)
//        {
//            mData->mCurrentRS.mAlphaBlendEnabled = true;
//            glEnable(GL_BLEND);
//        }
//
//        GLenum srcBlend = gOGLAlphaSrcBlend[mAlphaState->SrcBlend];
//        GLenum dstBlend = gOGLAlphaDstBlend[mAlphaState->DstBlend];
//        if (srcBlend != mData->mCurrentRS.mAlphaSrcBlend
//                || dstBlend != mData->mCurrentRS.mAlphaDstBlend)
//        {
//            mData->mCurrentRS.mAlphaSrcBlend = srcBlend;
//            mData->mCurrentRS.mAlphaDstBlend = dstBlend;
//            glBlendFunc(srcBlend, dstBlend);
//        }
//
//        if (mAlphaState->ConstantColor != mData->mCurrentRS.mBlendColor)
//        {
//            mData->mCurrentRS.mBlendColor = mAlphaState->ConstantColor;
//            glBlendColor(
//                mData->mCurrentRS.mBlendColor[0],
//                mData->mCurrentRS.mBlendColor[1],
//                mData->mCurrentRS.mBlendColor[2],
//                mData->mCurrentRS.mBlendColor[3]);
//        }
//    }
//    else
//    {
//        if (mData->mCurrentRS.mAlphaBlendEnabled)
//        {
//            mData->mCurrentRS.mAlphaBlendEnabled = false;
//            glDisable(GL_BLEND);
//        }
//    }
//
//    if (mAlphaState->CompareEnabled)
//    {
//        if (!mData->mCurrentRS.mAlphaCompareEnabled)
//        {
//            mData->mCurrentRS.mAlphaCompareEnabled = true;
//            glEnable(GL_ALPHA_TEST);
//        }
//
//        GLenum compare = gOGLAlphaCompare[mAlphaState->Compare];
//        float reference = mAlphaState->Reference;
//        if (compare != mData->mCurrentRS.mCompareFunction
//                || reference != mData->mCurrentRS.mAlphaReference)
//        {
//            mData->mCurrentRS.mCompareFunction = compare;
//            mData->mCurrentRS.mAlphaReference = reference;
//            glAlphaFunc(compare, reference);
//        }
//    }
//    else
//    {
//        if (mData->mCurrentRS.mAlphaCompareEnabled)
//        {
//            mData->mCurrentRS.mAlphaCompareEnabled = false;
//            glDisable(GL_ALPHA_TEST);
//        }
//    }
//};
//
//void Renderer::SetCullState(const CullState *cullState);
//void Renderer::SetDepthState(const DepthState *depthState);
//void Renderer::SetOffsetState(const OffsetState *offsetState);
//void Renderer::SetStencilState(const StencilState *stencilState);
//void Renderer::SetWireframeState(const WireframeState *wireState);
//
//void Renderer::Enable(const VertexBuffer *vbuffer,
//                      unsigned int streamIndex, unsigned int offset)
//{
//    // TODO: Renderer::Draw calls Enable, but using the default values
//    // of 0 for streamIndex and offset.  This means that the DX9 renderer can
//    // never set a streamIndex different from 1. The DX9 and OpenGL renderer
//    // always enabled the buffer starting at offset 0. Minimally, the
//    // streamIndex handling needs to be different.
//
//    VertexBufferMap::iterator iterator = m_vertexBuffers.find(vbuffer);
//    PlatformVertexBuffer *pvbuffer;
//    if (iterator != m_vertexBuffers.end())
//    {
//        pvbuffer = iterator->second;
//    }
//    else
//    {
//        // Lazy creation.
//        pvbuffer = new PlatformVertexBuffer(this, vbuffer);
//        m_vertexBuffers[vbuffer] = pvbuffer;
//    }
//
//    pvbuffer->Enable(this, vbuffer->GetElementSize(), streamIndex, offset);
//}
//
//
//void Renderer::Draw(const Visual *visual,
//                    const VisualEffectInstance *instance)
//{
//    if (!visual)
//    {
//        throw std::invalid_argument("The visual object must exist.\n");
//    }
//
//    if (!instance)
//    {
//        throw std::invalid_argument("The visual object must have an effect instance.\n");
//    }
//
//    const VertexFormat *vformat = visual->GetVertexFormat();
//    const VertexBuffer *vbuffer = visual->GetVertexBuffer();
//    const IndexBuffer  *ibuffer = visual->GetIndexBuffer();
//
//    // The OpenGL renderer requires the vertex buffer to be enabled before
//    // the vertex format is enabled.  The order is irrelevant for the
//    // DirectX9 renderer.
//    Enable(vbuffer);
//    Enable(vformat);
//    if (ibuffer)
//    {
//        Enable(ibuffer);
//    }
//
//    const int numPasses = instance->GetNumPasses();
//    for (int i = 0; i < numPasses; ++i)
//    {
//        const VisualPass *pass = instance->GetPass(i);
//        ShaderParameters *vparams = instance->GetVertexParameters(i);
//        ShaderParameters *pparams = instance->GetPixelParameters(i);
//        VertexShader *vshader = pass->GetVertexShader();
//        PixelShader *pshader = pass->GetPixelShader();
//
//        // Update any shader constants that vary during runtime.
//        vparams->UpdateConstants(visual, mCamera);
//        pparams->UpdateConstants(visual, mCamera);
//
//        // Set visual state.
//        SetBlendState(pass->GetAlphaState());
//        SetCullState(pass->GetCullState());
//        SetDepthState(pass->GetDepthState());
//        SetOffsetState(pass->GetOffsetState());
//        SetStencilState(pass->GetStencilState());
//        SetWireframeState(pass->GetWireState());
//
//        // Enable the shaders.
//        Enable(vshader, vparams);
//        Enable(pshader, pparams);
//
//        // Draw the primitive.
//        DrawPrimitive(visual);
//
//        // Disable the shaders.
//        Disable(vshader, vparams);
//        Disable(pshader, pparams);
//
//#if 0
//        // Restore visual state.
//        SetBlendState(mDefaultAlphaState);
//        SetCullState(mDefaultCullState);
//        SetDepthState(mDefaultDepthState);
//        SetOffsetState(mDefaultOffsetState);
//        SetStencilState(mDefaultStencilState);
//        SetWireframeState(mDefaultWireState);
//#endif
//    }
//
//    if (ibuffer)
//    {
//        Disable(ibuffer);
//    }
//
//    Disable(vformat);
//    Disable(vbuffer);
//}

}
