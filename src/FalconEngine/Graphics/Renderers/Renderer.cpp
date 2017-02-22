#include <FalconEngine/Graphics/Renderers/Renderer.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/BitmapText.h>
#include <FalconEngine/Graphics/Renderers/Camera.h>
#include <FalconEngine/Graphics/Renderers/Visual.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderers/VisualPass.h>
#include <FalconEngine/Graphics/Renderers/Shaders/Shader.h>
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture1d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture3d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>

#if FALCON_ENGINE_API_OPENGL
#include <FalconEngine/Graphics/Renderers/BitmapFontRenderer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLIndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLVertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLVertexFormat.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture1d.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture2d.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture3d.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTextureSampler.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLShader.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLShaderUniform.h>
#endif

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
void
Renderer::Initialize(int width, int height)
{
    InitializePlatform();

    assert(width > 0);
    assert(height > 0);

    mWidth = width;
    mHeight = height;

    mBlendStateDefault = new BlendState();
    mCullStateDefault = new CullState();
    mDepthTestStateDefault = new DepthTestState();
    mOffsetStateDefault = new OffsetState();
    mStencilTestStateDefault = new StencilTestState();
    mWireframeStateDefault = new WireframeState();

    mBlendStateCurrent = mBlendStateDefault;
    mCullStateCurrent = mCullStateDefault;
    mDepthTestStateCurrent = mDepthTestStateDefault;
    mOffsetStateCurrent = mOffsetStateDefault;
    mStencilTestStateCurrent = mStencilTestStateDefault;
    mWireframeStateCurrent = mWireframeStateDefault;

    mCamera = nullptr;
}

void
Renderer::Bind(const VertexBuffer *vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    // When has not been bound before
    if (mVertexBufferTable.find(vertexBuffer) == mVertexBufferTable.end())
    {
        mVertexBufferTable[vertexBuffer] = new PlatformVertexBuffer(vertexBuffer);
    }
}

void
Renderer::Unbind(const VertexBuffer *vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto veretxBufferPlatform = iter->second;
        delete veretxBufferPlatform;
        mVertexBufferTable.erase(iter);
    }
}

void
Renderer::Enable(const VertexBuffer *vertexBuffer, int bindingIndex, int offset, int stride)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto iter = mVertexBufferTable.find(vertexBuffer);
    PlatformVertexBuffer *vertexBufferPlatform;
    if (iter != mVertexBufferTable.end())
    {
        vertexBufferPlatform = iter->second;
    }
    else
    {
        vertexBufferPlatform = new PlatformVertexBuffer(vertexBuffer);
        mVertexBufferTable[vertexBuffer] = vertexBufferPlatform;
    }

    vertexBufferPlatform->Enable(bindingIndex, offset, stride);
}

void
Renderer::Disable(const VertexBuffer *vertexBuffer, int bindingIndex)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto vertexBufferPlatform = iter->second;
        vertexBufferPlatform->Disable(bindingIndex);
    }
}

void *
Renderer::Map(const VertexBuffer *vertexBuffer, BufferAccessMode mode)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto iter = mVertexBufferTable.find(vertexBuffer);
    PlatformVertexBuffer *vertexBufferPlatform;
    if (iter != mVertexBufferTable.end())
    {
        vertexBufferPlatform = iter->second;
    }
    else
    {
        vertexBufferPlatform = new PlatformVertexBuffer(vertexBuffer);
        mVertexBufferTable[vertexBuffer] = vertexBufferPlatform;
    }

    return vertexBufferPlatform->Map(mode);
}

void
Renderer::Unmap(const VertexBuffer *vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto vertexBufferPlatform = iter->second;
        vertexBufferPlatform->Unmap();
    }
}

void
Renderer::Update(const VertexBuffer *vertexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);

    int sourceDataByteNum = vertexBuffer->mDataByteNum;
    auto *sourceData = vertexBuffer->mData;
    void *destinationData = Map(vertexBuffer, BufferAccessMode::Write);
    memcpy(destinationData, sourceData, sourceDataByteNum);
    Unmap(vertexBuffer);
}

void
Renderer::Bind(const VertexFormat *vertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);

    if (mVertexFormatTable.find(vertexFormat) == mVertexFormatTable.end())
    {
        mVertexFormatTable[vertexFormat] = new PlatformVertexFormat(vertexFormat);
    }
}

void
Renderer::Unbind(const VertexFormat *vertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);

    auto iter = mVertexFormatTable.find(vertexFormat);
    if (iter != mVertexFormatTable.end())
    {
        auto *vertexFormatPlatform = iter->second;
        delete vertexFormatPlatform;
        mVertexFormatTable.erase(iter);
    }
}

void
Renderer::Enable(const VertexFormat *vertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);

    auto iter = mVertexFormatTable.find(vertexFormat);
    PlatformVertexFormat *vertexFormatPlatform;
    if (iter != mVertexFormatTable.end())
    {
        vertexFormatPlatform = iter->second;
    }
    else
    {
        vertexFormatPlatform = new PlatformVertexFormat(vertexFormat);
        mVertexFormatTable[vertexFormat] = vertexFormatPlatform;
    }

    vertexFormatPlatform->Enable();
}

void
Renderer::Disable(const VertexFormat *vertexFormat)
{
    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);

    auto iter = mVertexFormatTable.find(vertexFormat);
    if (iter != mVertexFormatTable.end())
    {
        auto vertexFormatPlatform = iter->second;
        vertexFormatPlatform->Disable();
    }
}

void
Renderer::Bind(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    if (mIndexBufferTable.find(indexBuffer) == mIndexBufferTable.end())
    {
        mIndexBufferTable[indexBuffer] = new PlatformIndexBuffer(indexBuffer);
    }
}

void
Renderer::Unbind(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    auto iter = mIndexBufferTable.find(indexBuffer);
    if (iter != mIndexBufferTable.end())
    {
        auto *indexBufferPlatform = iter->second;
        delete indexBufferPlatform;
        mIndexBufferTable.erase(iter);
    }
}

void
Renderer::Enable(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    auto iter = mIndexBufferTable.find(indexBuffer);
    PlatformIndexBuffer *indexBufferPlatform;
    if (iter != mIndexBufferTable.end())
    {
        indexBufferPlatform = iter->second;
    }
    else
    {
        indexBufferPlatform = new PlatformIndexBuffer(indexBuffer);
        mIndexBufferTable[indexBuffer] = indexBufferPlatform;
    }

    indexBufferPlatform->Enable();
}

void
Renderer::Disable(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    auto iter = mIndexBufferTable.find(indexBuffer);
    if (iter != mIndexBufferTable.end())
    {
        auto indexBufferPlatform = iter->second;
        indexBufferPlatform->Disable();
    }
}

void *
Renderer::Map(const IndexBuffer *indexBuffer, BufferAccessMode mode)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    auto iter = mIndexBufferTable.find(indexBuffer);
    PlatformIndexBuffer *indexBufferPlatform;
    if (iter != mIndexBufferTable.end())
    {
        indexBufferPlatform = iter->second;
    }
    else
    {
        indexBufferPlatform = new PlatformIndexBuffer(indexBuffer);
        mIndexBufferTable[indexBuffer] = indexBufferPlatform;
    }

    return indexBufferPlatform->Map(mode);
}

void
Renderer::Unmap(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    auto iter = mIndexBufferTable.find(indexBuffer);
    if (iter != mIndexBufferTable.end())
    {
        auto indexBufferPlatform = iter->second;
        indexBufferPlatform->Unmap();
    }
}

void
Renderer::Update(const IndexBuffer *indexBuffer)
{
    FALCON_ENGINE_CHECK_NULLPTR(indexBuffer);

    int sourceDataByteNum = indexBuffer->mDataByteNum;
    auto *sourceData = indexBuffer->mData;
    void *destinationData = Map(indexBuffer, BufferAccessMode::Write);
    memcpy(destinationData, sourceData, sourceDataByteNum);
    Unmap(indexBuffer);
}

void
Renderer::Enable(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    switch (texture->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture1d:
        Enable(textureUnit, reinterpret_cast<const Texture1d *>(texture));
        break;
    case TextureType::Texture2d:
        Enable(textureUnit, reinterpret_cast<const Texture2d *>(texture));
        break;
    case TextureType::Texture2dArray:
        Enable(textureUnit, reinterpret_cast<const Texture2dArray *>(texture));
        break;
    case TextureType::Texture3d:
        Enable(textureUnit, reinterpret_cast<const Texture3d *>(texture));
        break;
    case TextureType::TextureCube:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    default:
        FALCON_ENGINE_NOT_POSSIBLE();
    }
}

void
Renderer::Disable(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    switch (texture->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture1d:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture2d:
        Disable(textureUnit, reinterpret_cast<const Texture2d *>(texture));
        break;
    case TextureType::Texture2dArray:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture3d:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::TextureCube:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    default:
        FALCON_ENGINE_NOT_POSSIBLE();
    }
}

void
Renderer::Bind(const Texture2d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    if (mTexture2dTable.find(texture) == mTexture2dTable.end())
    {
        mTexture2dTable[texture] = new PlatformTexture2d(texture);
    }
}

void
Renderer::Unbind(const Texture2d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture2dTable.find(texture);
    if (iter != mTexture2dTable.end())
    {
        auto *texturePlatform = iter->second;
        delete texturePlatform;
        mTexture2dTable.erase(iter);
    }
}

void
Renderer::Enable(int textureUnit, const Texture2d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture2dTable.find(texture);
    PlatformTexture2d *texturePlatform;
    if (iter != mTexture2dTable.end())
    {
        texturePlatform = iter->second;
    }
    else
    {
        texturePlatform = new PlatformTexture2d(texture);
        mTexture2dTable[texture] = texturePlatform;
    }

    texturePlatform->Enable(textureUnit);
}

void
Renderer::Disable(int textureUnit, const Texture2d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture2dTable.find(texture);
    if (iter != mTexture2dTable.end())
    {
        auto texturePlatform = iter->second;
        texturePlatform->Disable(textureUnit);
    }
}

void *
Renderer::Map(const Texture2d *texture, int mipmapLevel, BufferAccessMode mode)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture2dTable.find(texture);
    PlatformTexture2d *texturePlatform;
    if (iter != mTexture2dTable.end())
    {
        texturePlatform = iter->second;
    }
    else
    {
        texturePlatform = new PlatformTexture2d(texture);
        mTexture2dTable[texture] = texturePlatform;
    }

    return texturePlatform->Map(mipmapLevel, mode);
}

void
Renderer::Unmap(const Texture2d *texture, int mipmapLevel)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture2dTable.find(texture);
    if (iter != mTexture2dTable.end())
    {
        auto texturePlatform = iter->second;
        texturePlatform->Unmap(mipmapLevel);
    }
}

void
Renderer::Update(const Texture2d *texture, int mipmapLevel)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    // TODO(Wuxiang): Add mipmap support.
    unsigned char *sourceData = texture->mData;
    void *targetData = Map(texture, mipmapLevel, BufferAccessMode::Write);
    memcpy(targetData, sourceData, texture->mDataByteNum);
    Unmap(texture, mipmapLevel);
}

void
Renderer::Bind(const Texture2dArray *textureArray)
{
    FALCON_ENGINE_CHECK_NULLPTR(textureArray);

    if (mTexture2dArrayTable.find(textureArray) == mTexture2dArrayTable.end())
    {
        mTexture2dArrayTable[textureArray] = new PlatformTexture2dArray(textureArray);
    }
}

void
Renderer::Unbind(const Texture2dArray *textureArray)
{
    FALCON_ENGINE_CHECK_NULLPTR(textureArray);

    auto iter = mTexture2dArrayTable.find(textureArray);
    if (iter != mTexture2dArrayTable.end())
    {
        auto *textureArrayPlatform = iter->second;
        delete textureArrayPlatform;
        mTexture2dArrayTable.erase(iter);
    }
}

void
Renderer::Enable(int textureUnit, const Texture2dArray *textureArray)
{
    FALCON_ENGINE_CHECK_NULLPTR(textureArray);

    auto iter = mTexture2dArrayTable.find(textureArray);
    PlatformTexture2dArray *textureArrayPlatform;
    if (iter != mTexture2dArrayTable.end())
    {
        textureArrayPlatform = iter->second;
    }
    else
    {
        textureArrayPlatform = new PlatformTexture2dArray(textureArray);
        mTexture2dArrayTable[textureArray] = textureArrayPlatform;
    }

    textureArrayPlatform->Enable(textureUnit);
}

void
Renderer::Disable(int textureUnit, const Texture2dArray *textureArray)
{
    FALCON_ENGINE_CHECK_NULLPTR(textureArray);

    auto iter = mTexture2dArrayTable.find(textureArray);
    if (iter != mTexture2dArrayTable.end())
    {
        auto textureArrayPlatform = iter->second;
        textureArrayPlatform->Disable(textureUnit);
    }
}

void
Renderer::Bind(const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    if (mSamplerTable.find(sampler) == mSamplerTable.end())
    {
        mSamplerTable[sampler] = new PlatformSampler(sampler);
    }
}

void
Renderer::Unbind(const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    auto iter = mSamplerTable.find(sampler);
    if (iter != mSamplerTable.end())
    {
        auto *samplerPlatform = iter->second;
        delete samplerPlatform;
        mSamplerTable.erase(iter);
    }
}

void
Renderer::Enable(int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    auto iter = mSamplerTable.find(sampler);
    PlatformSampler *samplerPlatform;
    if (iter != mSamplerTable.end())
    {
        samplerPlatform = iter->second;
    }
    else
    {
        samplerPlatform = new PlatformSampler(sampler);
        mSamplerTable[sampler] = samplerPlatform;
    }

    samplerPlatform->Enable(textureUnit);
}

void
Renderer::Disable(int textureUnit, const Sampler *sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    auto iter = mSamplerTable.find(sampler);
    if (iter != mSamplerTable.end())
    {
        auto samplerPlatform = iter->second;
        samplerPlatform->Disable(textureUnit);
    }
}

void
Renderer::Bind(Shader *shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    if (mShaderTable.find(shader) == mShaderTable.end())
    {
        mShaderTable[shader] = new PlatformShader(shader);
    }
}

void
Renderer::Unbind(const Shader *shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    auto iter = mShaderTable.find(shader);
    if (iter != mShaderTable.end())
    {
        auto platformShader = iter->second;
        delete platformShader;
        mShaderTable.erase(iter);
    }
}

void
Renderer::Enable(Shader *shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    auto iter = mShaderTable.find(shader);
    PlatformShader *platformShader;
    if (iter != mShaderTable.end())
    {
        platformShader = iter->second;
    }
    else
    {
        platformShader = new PlatformShader(shader);
        mShaderTable[shader] = platformShader;
    }

    platformShader->Enable();
}

void
Renderer::Disable(const Shader *shader)
{
    FALCON_ENGINE_CHECK_NULLPTR(shader);

    auto iter = mShaderTable.find(shader);
    if (iter != mShaderTable.end())
    {
        auto platformShader = iter->second;
        platformShader->Disable();
    }
}

void
Renderer::Enable(const VisualPass *pass)
{
    FALCON_ENGINE_CHECK_NULLPTR(pass);

    // Enable required shader textures.
    for (auto &textureUnit : pass->mShaderTextureTable)
    {
        Enable(textureUnit.first, textureUnit.second);
    }

    // Enable required shader samplers.
    for (auto &textureUnit : pass->mShaderSamplerTable)
    {
        Enable(textureUnit.first, textureUnit.second);
    }

    // Update required shader uniforms.
    for (int uniformIndex = 0; uniformIndex < pass->GetShaderUniformNum(); ++uniformIndex)
    {
        // NOTE(Wuxiang): At this point you are supposed to have uniform location
        // for each uniform. In principle, you should finish declaring all shader
        // uniform before this. The render engine would not repetitively check
        // whether each uniform has setup uniform location.

        // NOTE(Wuxiang): The location of the shader uniform would be stored in
        // shader's uniform table after the binding of the shader.
        auto uniform = pass->GetShaderUniform(uniformIndex);
        if (uniform->mLocation == 0)
        {
            auto shader = pass->GetShader();
            uniform->mLocation = shader->GetUniformLocation(uniform->mName);
        }

        if (uniform->mUpdated)
        {
            PlatformShaderUniform::UpdateContext(uniform);
        }
    }

    // Set pass' render states.
    SetBlendState(pass->GetBlendState());
    SetCullState(pass->GetCullState());
    SetDepthTestState(pass->GetDepthTestState());
    SetOffsetState(pass->GetOffsetState());
    SetStencilTestState(pass->GetStencilTestState());
    SetWireframeState(pass->GetWireframeState());
}

void
Renderer::Disable(const VisualPass *pass)
{
    FALCON_ENGINE_CHECK_NULLPTR(pass);

    // Disable required shader textures.
    for (auto &textureUnit : pass->mShaderTextureTable)
    {
        Disable(textureUnit.first, textureUnit.second);
    }

    // Disable required shader samplers.
    for (auto &textureUnit : pass->mShaderSamplerTable)
    {
        Disable(textureUnit.first, textureUnit.second);
    }
}

void
Renderer::Draw(Visual *visual)
{
    FALCON_ENGINE_CHECK_NULLPTR(visual);

    auto instance = visual->GetEffectInstance();
    Draw(visual, instance);
}

void
Renderer::Draw(const Visual *visual,
               VisualEffectInstance *instance)
{
    // NOTE(Wuxiang): The non-constness of instance comes from the fact that
    // during the binding of shader, the renderer would look up the shader's
    // location for each vertex attribute and each uniform.

    FALCON_ENGINE_CHECK_NULLPTR(visual);
    FALCON_ENGINE_CHECK_NULLPTR(instance);

    // NOTE(Wuxiang): Currently this function assume that all passes are using
    // same vertex attribute array, so that we don't switch vertex format between
    // the shader.

    // Enable vertex attribute array.
    auto vertexFormat = visual->GetVertexFormat();
    Enable(vertexFormat);

    // Enable vertex buffer.
    for (auto& vertexRecord : vertexFormat->mVertexBufferTable)
    {
        Enable(vertexRecord.GetVertexBuffer(),
               vertexRecord.GetIndex(),
               vertexRecord.GetOffset(),
               vertexRecord.GetStride());
    }

    auto indexBuffer = visual->GetIndexBuffer();
    if (indexBuffer)
    {
        // Enable index buffer.
        Enable(indexBuffer);
    }

    const int passNum = instance->GetPassNum();
    for (int passIndex = 0; passIndex < passNum; ++passIndex)
    {
        auto *pass = instance->GetPass(passIndex);
        auto *shader = pass->GetShader();

        // Enable the shader.
        Enable(shader);

        // Enable the pass.
        Enable(pass);

        // Draw the primitive.
        DrawPrimitive(visual);

        // Disable the pass.
        Disable(pass);

        // Disable the shader.
        Disable(shader);
    }

    // Disable index buffer.
    if (indexBuffer)
    {
        Disable(indexBuffer);
    }

    // Disable vertex buffer.
    for (auto& vertexRecord : vertexFormat->mVertexBufferTable)
    {
        Disable(vertexRecord.GetVertexBuffer(),
                vertexRecord.GetIndex());
    }

    // Disable vertex attribute array.
    Disable(vertexFormat);
}

void
Renderer::Draw(const VertexFormat *vertexFormat, const VertexBuffer *vertexBuffer, VisualEffectInstance *instance)
{
    // NOTE(Wuxiang): The non-constness of instance comes from the fact that
    // during the binding of shader, the renderer would look up the shader's
    // location for each vertex attribute and each uniform.

    FALCON_ENGINE_CHECK_NULLPTR(vertexFormat);
    FALCON_ENGINE_CHECK_NULLPTR(vertexBuffer);
    FALCON_ENGINE_CHECK_NULLPTR(instance);

    // NOTE(Wuxiang): Currently this function assume that all passes are using
    // same vertex attribute array, so that we don't switch vertex format between
    // the shader.

    // Enable vertex attribute array.
    Enable(vertexFormat);

    // Enable vertex buffer.
    for (auto& vertexRecord : vertexFormat->mVertexBufferTable)
    {
        Enable(vertexRecord.GetVertexBuffer(),
               vertexRecord.GetIndex(),
               vertexRecord.GetOffset(),
               vertexRecord.GetStride());
    }

    auto indexBuffer = visual->GetIndexBuffer();
    if (indexBuffer)
    {
        // Enable index buffer.
        Enable(indexBuffer);
    }

    const int passNum = instance->GetPassNum();
    for (int passIndex = 0; passIndex < passNum; ++passIndex)
    {
        auto *pass = instance->GetPass(passIndex);
        auto *shader = pass->GetShader();

        // Enable the shader.
        Enable(shader);

        // Enable the pass.
        Enable(pass);

        // Draw the primitive.
        DrawPrimitive(visual);

        // Disable the pass.
        Disable(pass);

        // Disable the shader.
        Disable(shader);
    }

    // Disable index buffer.
    if (indexBuffer)
    {
        Disable(indexBuffer);
    }

    // Disable vertex buffer.
    for (auto& vertexRecord : vertexFormat->mVertexBufferTable)
    {
        Disable(vertexRecord.GetVertexBuffer(),
                vertexRecord.GetIndex());
    }

    // Disable vertex attribute array.
    Disable(vertexFormat);
}

}
