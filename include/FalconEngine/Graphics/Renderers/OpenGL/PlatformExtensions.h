#pragma once

#include <map>

#include <FalconEngine/Graphics/Renderers/RendererExtensions.h>
#include <FalconEngine/Graphics/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Resources/Buffer.h>
#include <FalconEngine/Graphics/Shaders/Shader.h>

#include <FalconEngine/Graphics/States/BlendState.h>
#include <FalconEngine/Graphics/States/DepthState.h>
#include <FalconEngine/Graphics/States/StencilState.h>
#include "FalconEngine/Graphics/Scenes/Visual.h"

namespace FalconEngine {

extern const GLenum OpenGLBlendFactorSource        [int(BlendFactorSource::ENUM_COUNT)];
extern const GLenum OpenGLBlendFactorDestination   [int(BlendFactorDestination::ENUM_COUNT)];
extern const GLenum OpenGLDepthCompareFunction     [int(DepthCompareFunction::ENUM_COUNT)];

extern const GLenum OpenGLStencilFunction          [int(StencilFunction::ENUM_COUNT)];
extern const GLenum OpenGLStencilOperation         [int(StencilOperation::ENUM_COUNT)];

extern const GLint  OpenGLAttributeChannels        [int(VertexAttributeType::ENUM_COUNT)];
extern const GLuint OpenGLAttributeType            [int(VertexAttributeType::ENUM_COUNT)];

extern const GLuint OpenGLBufferAccessMode         [int(BufferAccessMode::ENUM_COUNT)];
extern const GLuint OpenGLBufferUsage              [int(BufferUsage::ENUM_COUNT)];

//extern GLint  OpenGLMinFilter[Shader::SF_QUANTITY];
//extern GLuint OpenGLTextureFormat[Texture::TF_QUANTITY];
//extern GLuint OpenGLTextureInternalFormat[Texture::TF_QUANTITY];
//extern GLuint OpenGLTextureTarget[Shader::ST_QUANTITY];
//extern GLuint OpenGLTextureTargetBinding[Shader::ST_QUANTITY];
//extern GLuint OpenGLTextureType[Texture::TF_QUANTITY];
//extern GLint  OpenGLWrapMode[Shader::SC_QUANTITY];
extern GLenum OpenGLPrimitiveType                  [int(VisualPrimitiveType::ENUM_COUNT)];

}
