#pragma once

#include <FalconEngine/Core.h>
#include <FalconEngine/Math.h>

#include <FalconEngine/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/BitmapFontRenderer.h>
#include <FalconEngine/Graphics/Renderers/BitmapGlyph.h>
#include <FalconEngine/Graphics/Renderers/BitmapLine.h>
#include <FalconEngine/Graphics/Renderers/BitmapText.h>
#include <FalconEngine/Graphics/Renderers/BitmapWord.h>
#include <FalconEngine/Graphics/Renderers/Camera.h>
#include <FalconEngine/Graphics/Renderers/Renderer.h>
#include <FalconEngine/Graphics/Renderers/Primitives.h>
#include <FalconEngine/Graphics/Renderers/Viewport.h>
#include <FalconEngine/Graphics/Renderers/Visual.h>
#include <FalconEngine/Graphics/Renderers/VisualEffect.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/VisualLines.h>
#include <FalconEngine/Graphics/Renderers/VisualPass.h>
#include <FalconEngine/Graphics/Renderers/VisualPoints.h>
#include <FalconEngine/Graphics/Renderers/VisualQuads.h>
#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>

#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture1d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture3d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBufferBinding.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexGroup.h>

#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniform.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderUniformManual.h>

#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>

#include <FalconEngine/Graphics/Scene/Light.h>
#include <FalconEngine/Graphics/Scene/Material.h>
#include <FalconEngine/Graphics/Scene/Mesh.h>
#include <FalconEngine/Graphics/Scene/Model.h>
#include <FalconEngine/Graphics/Scene/Node.h>
#include <FalconEngine/Graphics/Scene/Spatial.h>
