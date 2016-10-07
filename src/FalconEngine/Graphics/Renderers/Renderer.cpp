#include <FalconEngine/Graphics/Renderers/Renderer.h>

#include <FalconEngine/Core.h>

#if FALCON_ENGINE_USE_OPENGL
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformExtensions.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformIndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexFormat.h>

#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformRenderState.h>
#elif
#endif

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Renderer::Renderer():
    m_renderState(new PlatformRenderState())
{
}

Renderer::~Renderer()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void Renderer::Bind(const VertexFormat *vertexFormat)
{
    if (m_vertexFormats.find(vertexFormat) == m_vertexFormats.end())
    {
        m_vertexFormats[vertexFormat] = new PlatformVertexFormat(this, vertexFormat);
    }
}

void Renderer::Unbind(const VertexFormat *vertexFormat)
{
    VertexFormatMap::iterator iter = m_vertexFormats.find(vertexFormat);
    if (iter != m_vertexFormats.end())
    {
        PlatformVertexFormat *platformVertexFormat = iter->second;
        DeleteSafe(platformVertexFormat);
        m_vertexFormats.erase(iter);
    }
}

void Renderer::Enable(const VertexFormat *vertexFormat)
{
    VertexFormatMap::iterator iter = m_vertexFormats.find(vertexFormat);
    PlatformVertexFormat *platformVertexFormat;
    if (iter != m_vertexFormats.end())
    {
        platformVertexFormat = iter->second;
    }
    else
    {
        // Lazy creation.
        platformVertexFormat = new PlatformVertexFormat(this, vertexFormat);
        m_vertexFormats[vertexFormat] = platformVertexFormat;
    }

    platformVertexFormat->Enable(this);
}

void Renderer::Disable(const VertexFormat *vertexFormat)
{
    VertexFormatMap::iterator iter = m_vertexFormats.find(vertexFormat);
    if (iter != m_vertexFormats.end())
    {
        PlatformVertexFormat *platformVertexFormat = iter->second;
        platformVertexFormat->Disable(this);
    }
}

void Renderer::Bind(const VertexBuffer *vertexBuffer)
{
    if (m_vertexBuffers.find(vertexBuffer) == m_vertexBuffers.end())
    {
        m_vertexBuffers[vertexBuffer] = new PlatformVertexBuffer(this, vertexBuffer);
    }
}

void Renderer::Unbind(const VertexBuffer *vertexBuffer)
{
    VertexBufferMap::iterator iter = m_vertexBuffers.find(vertexBuffer);
    if (iter != m_vertexBuffers.end())
    {
        PlatformVertexBuffer *platformVertexBuffer = iter->second;
        DeleteSafe(platformVertexBuffer);
        m_vertexBuffers.erase(iter);
    }
}

void Renderer::Enable(const VertexBuffer *vertexBuffer, size_t offset)
{
    VertexBufferMap::iterator iter = m_vertexBuffers.find(vertexBuffer);
    PlatformVertexBuffer *platformVertexBuffer;
    if (iter != m_vertexBuffers.end())
    {
        platformVertexBuffer = iter->second;
    }
    else
    {
        // Lazy creation.
        platformVertexBuffer = new PlatformVertexBuffer(this, vertexBuffer);
        m_vertexBuffers[vertexBuffer] = platformVertexBuffer;
    }

    platformVertexBuffer->Enable(this, vertexBuffer->ElementSize(), offset);
}

void Renderer::Disable(const VertexBuffer *vertexBuffer)
{
    VertexBufferMap::iterator iter = m_vertexBuffers.find(vertexBuffer);
    if (iter != m_vertexBuffers.end())
    {
        PlatformVertexBuffer *platformVertexBuffer = iter->second;
        platformVertexBuffer->Disable(this);
    }
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/

}
