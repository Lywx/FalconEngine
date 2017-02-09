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
#include <FalconEngine/Graphics/Renderers/States/BlendState.h>
#include <FalconEngine/Graphics/Renderers/States/CullState.h>
#include <FalconEngine/Graphics/Renderers/States/DepthTestState.h>
#include <FalconEngine/Graphics/Renderers/States/OffsetState.h>
#include <FalconEngine/Graphics/Renderers/States/StencilTestState.h>
#include <FalconEngine/Graphics/Renderers/States/WireframeState.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture1d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture3d.h>
#include <FalconEngine/Graphics/Renderers/Resources/TextureSampler.h>
#include <FalconEngine/Graphics/Shaders/Shader.h>

#if FALCON_ENGINE_API_OPENGL
#include <FalconEngine/Graphics/Renderers/BitmapFontRenderer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLIndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLVertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture1d.h>
#include <FalconEngine/Graphics/Renderers/Platforms/OpenGL/OGLTexture2d.h>
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
    // When has not been bound before
    if (mVertexBufferTable.find(vertexBuffer) == mVertexBufferTable.end())
    {
        mVertexBufferTable[vertexBuffer] = new PlatformVertexBuffer(vertexBuffer);
    }
}

void
Renderer::Unbind(const VertexBuffer *vertexBuffer)
{
    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto veretxBufferPlatform = iter->second;
        delete veretxBufferPlatform;
        mVertexBufferTable.erase(iter);
    }
}

void
Renderer::Enable(const VertexBuffer *vertexBuffer)
{
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

    vertexBufferPlatform->Enable();
}

void
Renderer::Disable(const VertexBuffer *vertexBuffer)
{
    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto vertexBufferPlatform = iter->second;
        vertexBufferPlatform->Disable();
    }
}

void *
Renderer::Map(const VertexBuffer *vertexBuffer, BufferAccessMode mode)
{
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
    int sourceDataByteNum = vertexBuffer->mDataByteNum;
    auto *sourceData = vertexBuffer->mData;
    void *destinationData = Map(vertexBuffer, BufferAccessMode::Write);
    memcpy(destinationData, sourceData, sourceDataByteNum);
    Unmap(vertexBuffer);
}

void
Renderer::Bind(const IndexBuffer *indexBuffer)
{
    if (mIndexBufferTable.find(indexBuffer) == mIndexBufferTable.end())
    {
        mIndexBufferTable[indexBuffer] = new PlatformIndexBuffer(indexBuffer);
    }
}

void
Renderer::Unbind(const IndexBuffer *indexBuffer)
{
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
    int sourceDataByteNum = indexBuffer->mDataByteNum;
    auto *sourceData = indexBuffer->mData;
    void *destinationData = Map(indexBuffer, BufferAccessMode::Write);
    memcpy(destinationData, sourceData, sourceDataByteNum);
    Unmap(indexBuffer);
}

void
Renderer::Enable(int textureUnit, const Texture *texture)
{
    switch (texture->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture1d:
        FALCON_ENGINE_NOT_SUPPORT();
        break;
    case TextureType::Texture2d:
        Enable(textureUnit, reinterpret_cast<const Texture2d *>(texture));
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
Renderer::Disable(int textureUnit, const Texture *texture)
{
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
    if (mTexture2dTable.find(texture) == mTexture2dTable.end())
    {
        mTexture2dTable[texture] = new PlatformTexture2d(texture);
    }
}

void
Renderer::Unbind(const Texture2d *texture)
{
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
    // TODO(Wuxiang): Add mipmap support.
    unsigned char *sourceData = texture->mData;
    void *targetData = Map(texture, mipmapLevel, BufferAccessMode::Write);
    memcpy(targetData, sourceData, texture->mDataByteNum);
    Unmap(texture, mipmapLevel);
}

void
Renderer::Bind(const TextureSampler *sampler)
{
    if (mTextureSamplerTable.find(sampler) == mTextureSamplerTable.end())
    {
        mTextureSamplerTable[sampler] = new PlatformTextureSampler(sampler);
    }
}

void
Renderer::Unbind(const TextureSampler *sampler)
{
    auto iter = mTextureSamplerTable.find(sampler);
    if (iter != mTextureSamplerTable.end())
    {
        auto *samplerPlatform = iter->second;
        delete samplerPlatform;
        mTextureSamplerTable.erase(iter);
    }
}

void
Renderer::Enable(int textureUnit, TextureSampler *sampler)
{
    auto iter = mTextureSamplerTable.find(sampler);
    PlatformTextureSampler *samplerPlatform;
    if (iter != mTextureSamplerTable.end())
    {
        samplerPlatform = iter->second;
    }
    else
    {
        samplerPlatform = new PlatformTextureSampler(sampler);
        mTextureSamplerTable[sampler] = samplerPlatform;
    }

    samplerPlatform->Enable(textureUnit);
}

void
Renderer::Disable(int textureUnit, TextureSampler *sampler)
{
    auto iter = mTextureSamplerTable.find(sampler);
    if (iter != mTextureSamplerTable.end())
    {
        auto samplerPlatform = iter->second;
        samplerPlatform->Disable(textureUnit);
    }
}

void
Renderer::Bind(const Shader *shader)
{
    if (mShaderTable.find(shader) == mShaderTable.end())
    {
        mShaderTable[shader] = new PlatformShader(shader);
    }
}

void
Renderer::Unbind(const Shader *shader)
{
    auto iter = mShaderTable.find(shader);
    if (iter != mShaderTable.end())
    {
        auto platformShader = iter->second;
        delete platformShader;
        mShaderTable.erase(iter);
    }
}

void
Renderer::Enable(const Shader *shader)
{
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
        //  TODO(Wuxiang 2017-01-25 13:21): Wrong!
        auto *uniform = pass->GetShaderUniform(uniformIndex);
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
Renderer::DrawString(BitmapFont *font, float fontSize, Vector2f textPosition, const BitmapText *text, const Color textColor, float textLineWidth)
{
    DrawString()
}

void
Renderer::DrawString(BitmapFont *font, float fontSize, Vector2f textPosition, const std::string& text, const Color textColor, float textLineWidth)
{
}

void
Renderer::PrepareString(BitmapFont *font, Shader *textShader, BitmapText *textGroup)
{
    static auto textLines = vector<BitmapLine>();
    textLines.clear();

    int textGlyphCount = CreateLines(font, textGroup, textLines);

    // TODO(Wuxiang): Add multiple font and shader support. Replace the default with shader specific attribute vector.
    // Fill the vertex attribute into the buffer
    CreateAttributes(font, textGroup.m_fontSize, Vector2f(textGroup.m_textBounds.x, textGroup.m_textBounds.y), Vector4f(textColor), textLines, m_textShaderDefaultAttributes);

    // Find the render group this group of text belongs to.
    int  renderGroupIndex;
    bool renderGroupFound = false;
    for (renderGroupIndex = 0; renderGroupIndex < m_fontRenderGroups.size(); ++renderGroupIndex)
    {
        if (m_fontRenderGroups[renderGroupIndex].m_font == &font
                && m_fontRenderGroups[renderGroupIndex].m_textShader == &textShader)
        {
            renderGroupFound = true;
            break;
        }
    }

    if (renderGroupFound)
    {
        m_fontRenderGroups[renderGroupIndex].m_textVertexCount += textGlyphCount * 6;
    }
    else
    {
        // TODO(Wuxiang): Add multiple font and shader support. Replace the default attributes, buffer, vao with shader specific ones.
        BitmapFontRenderGroup renderGroup;
        renderGroup.m_font = &font;
        renderGroup.m_textShader = &textShader;
        renderGroup.m_textShaderAttributes = &m_textShaderDefaultAttributes;
        renderGroup.m_textShaderBuffer = m_textShaderDefaultBuffer;
        renderGroup.m_textShaderVao = m_textShaderDefaultVao;
        renderGroup.m_textVertexCount = textGlyphCount * 6;
        m_fontRenderGroups.push_back(renderGroup);
    }

    m_fontRenderGroupsDirty = true;

}

void
Renderer::Draw(const Visual *visual)
{
    auto instance = visual->GetEffectInstance();
    Draw(visual, instance);
}

void
Renderer::Draw(const Visual *visual,
               const VisualEffectInstance *instance)
{
    if (!visual)
    {
        throw invalid_argument("The visual object must exist.");
    }

    if (!instance)
    {
        throw invalid_argument("The visual object must have an effect instance.");
    }

    const VertexBuffer *vertexBuffer = visual->GetVertexBuffer();
    const IndexBuffer *indexBuffer = visual->GetIndexBuffer();

    Enable(vertexBuffer);
    if (indexBuffer)
    {
        Enable(indexBuffer);
    }

    const int passNum = instance->GetPassNum();
    for (int passIndex = 0; passIndex < passNum; ++passIndex)
    {
        const auto *pass = instance->GetPass(passIndex);
        const auto *shader = pass->GetShader();

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

    if (indexBuffer)
    {
        Disable(indexBuffer);
    }

    Disable(vertexBuffer);
}

}
