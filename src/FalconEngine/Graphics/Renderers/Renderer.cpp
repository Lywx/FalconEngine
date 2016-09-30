#include <FalconEngine/Graphics/Renderers/Renderer.h>

#define FALCON_ENGINE_OPENGL 1
#if FALCON_ENGINE_OPENGL
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformExtensions.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformIndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformVertexFormat.h>

#include <FalconEngine/Graphics/Renderers/OpenGL/PlatformRenderState.h>
#endif

namespace FalconEngine {

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Renderer::Renderer(): m_renderState(new PlatformRenderState())
{
}

Renderer::~Renderer()
{
}

}
