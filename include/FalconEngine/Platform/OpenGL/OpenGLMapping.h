#pragma once

#include <FalconEngine/Core/Macro.h>

#if defined(FALCON_ENGINE_API_OPENGL)
#include <FalconEngine/Graphics/Renderer/Primitive.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Platform/OpenGL/OpenGLLib.h>

namespace FalconEngine
{

FALCON_ENGINE_API extern const GLuint OpenGLBufferAccessModeBit[int(ResourceMapAccessMode::Count)];
FALCON_ENGINE_API extern const GLuint OpenGLBufferFlushModeBit[int(ResourceMapFlushMode::Count)];
FALCON_ENGINE_API extern const GLuint OpenGLBufferSynchronizationModeBit[int(ResourceMapSyncMode::Count)];

FALCON_ENGINE_API GLuint              OpenGLBufferUsage(ResourceCreationAccessMode mode, ResourceCreationAccessUsage usage);

FALCON_ENGINE_API extern const GLuint OpenGLTextureType[int(TextureFormat::Count)];               // Texture element type
FALCON_ENGINE_API extern const GLuint OpenGLTextureFormat[int(TextureFormat::Count)];             // Texture format
FALCON_ENGINE_API extern const GLuint OpenGLTextureInternalFormat[int(TextureFormat::Count)];     // Texture internal format
FALCON_ENGINE_API extern const GLuint OpenGLTextureTarget[int(TextureType::Count)];
FALCON_ENGINE_API extern const GLuint OpenGLTextureTargetBinding[int(TextureType::Count)];

FALCON_ENGINE_API extern const GLint  OpenGLSamplerFilterMode[int(SamplerMinificationFilter::Count)];
FALCON_ENGINE_API extern const int    OpenGLSamplerMipmapMode[4];
FALCON_ENGINE_API extern const GLint  OpenGLSamplerWrapMode[int(SamplerWrapMode::Count)];

FALCON_ENGINE_API extern const GLenum OpenGLBlendFactorSource[int(BlendSourceFactor::Count)];
FALCON_ENGINE_API extern const GLenum OpenGLBlendFactorDestination[int(BlendDestinationFactor::Count)];

FALCON_ENGINE_API extern const GLenum OpenGLDepthFunction[int(DepthFunction::Count)];

FALCON_ENGINE_API extern const GLenum OpenGLStencilFunction[int(StencilFunction::Count)];
FALCON_ENGINE_API extern const GLenum OpenGLStencilOperation[int(StencilOperation::Count)];

FALCON_ENGINE_API extern const GLuint OpenGLShaderAttributeType[int(VertexAttributeType::Count)];
FALCON_ENGINE_API extern const GLenum OpenGLShaderType[int(ShaderType::Count)];

FALCON_ENGINE_API extern const GLenum OpenGLPrimitiveType[int(PrimitiveType::Count)];

}

#endif