#pragma once

#include <FalconEngine/Core.h>
#include <FalconEngine/Math.h>

#include <FalconEngine/GraphicsInclude.h>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/PrimitivePoints.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveQuads.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Viewport.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>

#include <FalconEngine/Graphics/Renderer/Font/BitmapFont.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFontRenderer.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapGlyph.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapLine.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapText.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapWord.h>

#include <FalconEngine/Graphics/Renderer/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resources/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture1d.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture3d.h>
#include <FalconEngine/Graphics/Renderer/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexBufferBinding.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resources/VertexGroup.h>

#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniform.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformManual.h>

#include <FalconEngine/Graphics/Renderer/Scene/Light.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/MeshEffect.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Graphics/Renderer/Scene/Spatial.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>

#include <FalconEngine/Graphics/Renderer/States/BlendState.h>
#include <FalconEngine/Graphics/Renderer/States/CullState.h>
#include <FalconEngine/Graphics/Renderer/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/States/WireframeState.h>

#include <FalconEngine/Graphics/Scene/Character.h>
#include <FalconEngine/Graphics/Scene/Lamp.h>
