#pragma once

#include <map>

#include <FalconEngine/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/VertexFormat.h>
#include <FalconEngine/Graphics/Renderers/Buffer.h>
#include <FalconEngine/Graphics/Renderers/Texture.h>
#include <FalconEngine/Graphics/Shaders/Shader.h>

#include <FalconEngine/Graphics/States/BlendState.h>
#include <FalconEngine/Graphics/States/DepthState.h>
#include <FalconEngine/Graphics/States/StencilState.h>

namespace FalconEngine
{

extern const GLuint OpenGLTextureFormat[int(Texture::TF_QUANTITY)];
extern const GLuint OpenGLTextureInternalFormat[int(Texture::TF_QUANTITY)];
extern const GLuint OpenGLTextureTarget[int(Shader::ST_QUANTITY)];
extern const GLuint OpenGLTextureTargetBinding[int(Shader::ST_QUANTITY)];
extern const GLuint OpenGLTextureType[int(TextureType::Count)];

extern const GLenum OpenGLBlendFactorSource[int(BlendFactorSource::Count)];
extern const GLenum OpenGLBlendFactorDestination[int(BlendFactorDestination::Count)];
extern const GLenum OpenGLDepthCompareFunction[int(DepthCompareFunction::Count)];

extern const GLenum OpenGLStencilFunction[int(StencilFunction::Count)];
extern const GLenum OpenGLStencilOperation[int(StencilOperation::Count)];

extern const GLint  OpenGLAttributeChannels[int(VertexAttributeType::ENUM_COUNT)];
extern const GLuint OpenGLAttributeType[int(VertexAttributeType::ENUM_COUNT)];

extern const GLuint OpenGLBufferAccessMode[int(BufferAccessMode::Count)];
extern const GLuint OpenGLBufferUsage[int(BufferUsage::Count)];

//extern GLint  OpenGLMinFilter[Shader::SF_QUANTITY];
//extern GLint  OpenGLWrapMode[Shader::SC_QUANTITY];
extern GLenum OpenGLPrimitiveType[int(VisualPrimitiveType::ENUM_COUNT)];

}
