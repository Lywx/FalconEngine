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

class FALCON_ENGINE_GRAPHICS_ITEM Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    typedef std::map<const VertexFormat *, PlatformVertexFormat *> VertexFormatMap;
    typedef std::map<const VertexBuffer *, PlatformVertexBuffer *> VertexBufferMap;
    typedef std::map<const IndexBuffer *,  PlatformIndexBuffer *>  IndexBufferMap;

    /************************************************************************/
    // Vertex format management. The vertex format object must have been
    // already allocated and its attributes and stride set by the application
    // code.

    // @Summary: Register the vertex format with the platform dependent one in the renderer
    // implementation. If there is a mapping existing, then do nothing.
    void Bind(const VertexFormat *vertexFormat);

    // @Summary: Unregister the vertex format with the platform dependent one in the renderer
    // implementation and delete the binded platform dependent vertex format.
    void Unbind(const VertexFormat *vertexFormat);

    // @Summary: Use the corresponding platform dependent vertex format to launch the renderer
    // into desirable state. If there is no corresponding platform dependent
    // vertex format, then create one and bind it on-the-fly.
    void Enable(const VertexFormat *vertexFormat);

    // @Summary: Use the corresponding platform dependent vertex format to disable used
    // state. If there is no corresponding platform dependent vertex format,
    // then do nothing.
    void Disable(const VertexFormat *vertexFormat);

    // NOTE(Wuxiang): I don't have the global version that allow controlling
    // multiple renderer in one method, since I don't support multi-threaded
    // rendering at this stage.

    /************************************************************************/
    // Vertex buffer management. The vertex buffer object must have been
    // already allocated by the application code.

    void Bind(const VertexBuffer *vertexBuffer);

    void Unbind(const VertexBuffer *vertexBuffer);

    void Enable(const VertexBuffer *vertexBuffer, size_t offset = 0);

    void Disable(const VertexBuffer *vertexBuffer);

    void Unlock(const VertexBuffer *vertexBuffer);

    void Update(const VertexBuffer *vertexBuffer);

    /************************************************************************/
    // Index buffer management. The index buffer object must have been
    // already allocated by the application code.

    /************************************************************************/
    // Global state management.

    void SetBlendState(const BlendState *alphaState);
    void SetCullState(const CullState *cullState);
    void SetDepthState(const DepthState *depthState);
    void SetOffsetState(const OffsetState *offsetState);
    void SetStencilState(const StencilState *stencilState);
    void SetWireframeState(const WireframeState *wireState);

    /************************************************************************/
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

    VertexBufferMap m_vertexBuffers;
    VertexFormatMap m_vertexFormats;
    IndexBufferMap  m_indexBuffers;

    // TODO(Wuxiang)
    PlatformRenderState *m_renderState;
};

}