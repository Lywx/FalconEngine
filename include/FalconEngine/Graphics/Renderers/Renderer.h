#pragma once

#include <map>

#include <FalconEngine/Graphics/Scenes/Visual.h>

#include <FalconEngine/Graphics/Shaders/VisualEffectInstance.h>

#include <FalconEngine/Graphics/States/BlendState.h>
#include <FalconEngine/Graphics/States/CullState.h>
#include <FalconEngine/Graphics/States/DepthState.h>
#include <FalconEngine/Graphics/States/OffsetState.h>
#include <FalconEngine/Graphics/States/StencilState.h>
#include <FalconEngine/Graphics/States/WireframeState.h>

#include <FalconEngine/Graphics/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Resources/VertexBuffer.h>

namespace FalconEngine {

class PlatformIndexBuffer;
class PlatformVertexFormat;
class PlatformVertexBuffer;

class PlatformRenderState;

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    typedef std::map<const VertexFormat *, PlatformVertexFormat *> VertexFormatMap;
    typedef std::map<const VertexBuffer *, PlatformVertexBuffer *> VertexBufferMap;
    typedef std::map<const IndexBuffer *,  PlatformIndexBuffer *>  IndexBufferMap;

    void Enable(const VertexBuffer *vbuffer, unsigned int streamIndex = 0, unsigned int offset = 0);

    /************************************************************************/
    /* States                                                               */
    /************************************************************************/
    void SetBlendState(const BlendState *alphaState);
    void SetCullState(const CullState *cullState);
    void SetDepthState(const DepthState *depthState);
    void SetOffsetState(const OffsetState *offsetState);
    void SetStencilState(const StencilState *stencilState);
    void SetWireframeState(const WireframeState *wireState);

    // Viewport management.  The viewport is specified in right-handed screen
    // coordinates.  The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    void SetViewport(int xPosition, int yPosition, int width, int height);
    void GetViewport(int& xPosition, int& yPosition, int& width, int& height) const;
    void SetDepthRange(float zMin, float zMax);
    void GetDepthRange(float& zMin, float& zMax) const;
    void Resize(int width, int height);

    // Support for clearing the color, depth, and stencil buffers.
    void ClearColorBuffer();
    void ClearDepthBuffer();
    void ClearStencilBuffer();
    void ClearBuffers();
    void ClearColorBuffer(int x, int y, int w, int h);
    void ClearDepthBuffer(int x, int y, int w, int h);
    void ClearStencilBuffer(int x, int y, int w, int h);
    void ClearBuffers(int x, int y, int w, int h);
    void DisplayColorBuffer();

    // Support for masking color channels during drawing.
    void SetColorMask(bool allowRed, bool allowGreen,
                      bool allowBlue, bool allowAlpha);


    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    void DrawString(const int x, const int y, const std::string& str, const Vector4f& color);
    void Draw(const Visual *visual, const VisualEffectInstance *instance);
    void Draw(const Visual *visual);

private:
    void DrawPrimitive(const Visual *visual);

    // TODO(Wuxiang)
    VertexBufferMap m_vertexBuffers;

    // TODO(Wuxiang)
    PlatformRenderState *m_renderState;
};

}