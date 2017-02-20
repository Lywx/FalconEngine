#pragma once

#include <map>

#include <FalconEngine/Graphics/GraphicsInclude.h>

#if FALCON_ENGINE_API_OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#endif

#include <FalconEngine/Graphics/Renderers/Primitives.h>
#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>
#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderVertexAttribute.h>

#define FALCON_ENGINE_BUFFER_OFFSET(offset) ((void *)(offset))

namespace FalconEngine
{

extern const GLuint OpenGLBufferAccessMode[int(BufferAccessMode::Count)];
extern const GLuint OpenGLBufferUsage[int(BufferUsage::Count)];

extern const GLuint OpenGLTextureType[int(TextureFormat::Count)];               // Texture element type
extern const GLuint OpenGLTextureFormat[int(TextureFormat::Count)];             // Texture format
extern const GLuint OpenGLTextureInternalFormat[int(TextureFormat::Count)];     // Texture internal format
extern const GLuint OpenGLTextureTarget[int(TextureType::Count)];
extern const GLuint OpenGLTextureTargetBinding[int(TextureType::Count)];

extern const GLint  OpenGLSamplerFilterMode[int(SamplerMinificationFilter::Count)];
extern const GLint  OpenGLSamplerWrapMode[int(SamplerWrapMode::Count)];

extern const GLenum OpenGLBlendFactorSource[int(BlendSourceFactor::Count)];
extern const GLenum OpenGLBlendFactorDestination[int(BlendDestinationFactor::Count)];

extern const GLenum OpenGLDepthFunction[int(DepthFunction::Count)];

extern const GLenum OpenGLStencilFunction[int(StencilFunction::Count)];
extern const GLenum OpenGLStencilOperation[int(StencilOperation::Count)];

extern const GLuint OpenGLShaderAttributeType[int(ShaderVertexAttributeType::Count)];
extern const GLenum OpenGLShaderType[int(ShaderType::Count)];

extern const GLenum OpenGLPrimitiveType[int(PrimitiveType::Count)];

// @return previous bound texture
GLuint
BindTexture(TextureType textureType, GLuint texture);

// @return previous bound texture
GLuint
GetBoundTexture(TextureType textureType);

// @return previous bound sampler
GLuint
BindSampler(GLuint textureUnit, GLuint sampler);

}
