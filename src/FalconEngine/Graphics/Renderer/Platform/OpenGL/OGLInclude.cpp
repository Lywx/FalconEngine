#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLInclude.h>

namespace FalconEngine
{

const GLuint OpenGLBufferAccessMode[int(BufferAccessMode::Count)] =
{
    GL_INVALID_ENUM,

    GL_READ_ONLY,
    GL_READ_WRITE,
    GL_WRITE_ONLY,
};

const GLuint OpenGLBufferUsage[int(BufferUsage::Count)] =
{
    GL_INVALID_ENUM,

    GL_STATIC_DRAW,
    GL_STREAM_DRAW,
    GL_DYNAMIC_DRAW,
};

const GLuint OpenGLTextureType[int(TextureFormat::Count)] =
{
    0,                // None
    GL_UNSIGNED_BYTE, // R8G8B8A8
};

const GLuint OpenGLTextureFormat[int(TextureFormat::Count)] =
{
    0,       // None
    GL_RGBA, // R8G8B8A8
};

const GLuint OpenGLTextureInternalFormat[int(TextureFormat::Count)] =
{
    0,        // None
    GL_RGBA8, // R8G8B8A8
};

const GLuint OpenGLTextureTarget[int(TextureType::Count)] =
{
    0,                   // None

    GL_TEXTURE_1D,       // 1d
    GL_TEXTURE_2D,       // 2d
    GL_TEXTURE_2D_ARRAY, // 2d array
    GL_TEXTURE_3D,       // 3d
    GL_TEXTURE_CUBE_MAP  // Cube
};

const GLuint OpenGLTextureTargetBinding[int(TextureType::Count)] =
{
    0,                           // None

    GL_TEXTURE_BINDING_1D,       // 1d
    GL_TEXTURE_BINDING_2D,       // 2d
    GL_TEXTURE_BINDING_2D_ARRAY, // 2d array
    GL_TEXTURE_BINDING_3D,       // 3d
    GL_TEXTURE_BINDING_CUBE_MAP  // Cube
};

const GLint OpenGLSamplerFilterMode[int(SamplerMinificationFilter::Count)] =
{
    GL_NEAREST,                 // Nearest
    GL_LINEAR,                  // Linear

    GL_NEAREST_MIPMAP_NEAREST,  // NearestMipmapNearest
    GL_NEAREST_MIPMAP_LINEAR,   // NearestMipmapLinear
    GL_LINEAR_MIPMAP_NEAREST,   // LinearMipmapNearest
    GL_LINEAR_MIPMAP_LINEAR     // LinearMipmapLinear
};

const GLint OpenGLSamplerWrapMode[int(SamplerWrapMode::Count)] =
{
    GL_CLAMP_TO_BORDER,  // ClampToBorder
    GL_CLAMP_TO_EDGE,    // ClampToEdge
    GL_REPEAT,           // Repeat
    GL_MIRRORED_REPEAT,  // RepeatMirrored
};

const GLenum OpenGLBlendFactorSource[int(BlendSourceFactor::Count)] =
{
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_CONSTANT_COLOR,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_SRC_ALPHA_SATURATE,
    GL_SRC1_COLOR,
    GL_ONE_MINUS_SRC1_COLOR,
    GL_SRC1_ALPHA,
    GL_ONE_MINUS_SRC1_ALPHA,
};

const GLenum OpenGLBlendFactorDestination[int(BlendDestinationFactor::Count)] =
{
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_CONSTANT_COLOR,
    GL_ONE_MINUS_CONSTANT_COLOR,
    GL_CONSTANT_ALPHA,
    GL_ONE_MINUS_CONSTANT_ALPHA,
    GL_SRC_ALPHA_SATURATE,
    GL_SRC1_COLOR,
    GL_ONE_MINUS_SRC1_COLOR,
    GL_SRC1_ALPHA,
    GL_ONE_MINUS_SRC1_ALPHA,
};

const GLenum OpenGLDepthFunction[int(DepthFunction::Count)] =
{
    GL_NEVER,    // Never passes.
    GL_LESS,     // Passes if the incoming depth value is less than the stored depth value.
    GL_EQUAL,    // Passes if the incoming depth value is equal to the stored depth value.
    GL_LEQUAL,   // Passes if the incoming depth value is less than or equal to the stored depth value.
    GL_GREATER,  // Passes if the incoming depth value is greater than the stored depth value.
    GL_NOTEQUAL, // Passes if the incoming depth value is not equal to the stored depth value.
    GL_GEQUAL,   // Passes if the incoming depth value is greater than or equal to the stored depth value.
    GL_ALWAYS,
};

const GLenum OpenGLStencilFunction[int(StencilFunction::Count)] =
{
    GL_NEVER,
    GL_ALWAYS,
    GL_LESS,
    GL_LEQUAL,
    GL_EQUAL,
    GL_GEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
};

const GLenum OpenGLStencilOperation[int(StencilOperation::Count)] =
{
    GL_KEEP,
    GL_ZERO,
    GL_REPLACE,
    GL_INCR,
    GL_DECR,
    GL_INVERT,
    GL_INCR_WRAP,
    GL_DECR_WRAP,
};

const GLenum OpenGLPrimitiveType[int(PrimitiveType::Count)] =
{
    0,             // None

    GL_POINTS,     // Point
    GL_LINES,      // Line
    GL_LINE_STRIP, // Line Strip
    GL_TRIANGLES,  // Triangle
};

const GLuint OpenGLShaderAttributeType[int(VertexAttributeType::Count)] =
{
    0,        // None

    GL_FLOAT, // Float
    GL_FLOAT, // FloatVec2
    GL_FLOAT, // FloatVec3
    GL_FLOAT, // FloatVec4

    GL_INT,   // Int
    GL_INT,   // IntVec2
    GL_INT,   // IntVec3
    GL_INT,   // IntVec4
};

const GLenum OpenGLShaderType[int(ShaderType::Count)] =
{
    GL_VERTEX_SHADER,
    GL_GEOMETRY_SHADER,
    GL_FRAGMENT_SHADER
};

GLuint
BindTexture(TextureType textureType, GLuint texture)
{
    GLint textureBoundCurrent = 0;
    glGetIntegerv(OpenGLTextureTargetBinding[int(textureType)], &textureBoundCurrent);
    glBindTexture(OpenGLTextureTarget[int(textureType)], texture);
    return static_cast<GLuint>(textureBoundCurrent);
}

GLuint
GetBoundTexture(TextureType textureType)
{
    GLint textureBoundCurrent = 0;
    glGetIntegerv(OpenGLTextureTargetBinding[int(textureType)], &textureBoundCurrent);
    return static_cast<GLuint>(textureBoundCurrent);
}

GLuint
BindSampler(GLuint textureUnit, GLuint sampler)
{
    GLint samplerBoundCurrent = 0;
    glGetIntegerv(GL_SAMPLER_BINDING, &samplerBoundCurrent);
    glBindSampler(textureUnit, sampler);
    return static_cast<GLuint>(samplerBoundCurrent);
}

}
