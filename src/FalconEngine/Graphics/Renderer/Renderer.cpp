#include <FalconEngine/Graphics/Renderer/Renderer.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;

#include <FalconEngine/Context/GameEngineSettings.h>
#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/VisualEffect.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstancePass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Font/Font.h>
#include <FalconEngine/Graphics/Renderer/Font/FontRenderer.h>
#include <FalconEngine/Graphics/Renderer/Font/FontText.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture3d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>


#if defined(FALCON_ENGINE_WINDOW_GLFW)
#include <FalconEngine/Context/Platform/GLFW/GLFWGameEngineData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLIndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLVertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLVertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture1d.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture2d.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTexture3d.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLTextureSampler.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLRendererData.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShader.h>
#include <FalconEngine/Graphics/Renderer/Platform/OpenGL/OGLShaderUniform.h>
#endif

namespace FalconEngine
{

void
PlatformRendererDataDeleter::operator()(PlatformRendererData *rendererData)
{
    delete rendererData;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Renderer::Renderer(GameEngineData *gameEngineData, GameEngineSettings *gameEngineSettings)
{
    InitializeData(gameEngineSettings);
    InitializePlatform(gameEngineData);
}

Renderer::~Renderer()
{
    DestroyData();
    DestroyPlatform();
}

/************************************************************************/
/* Initialization and Destroy                                           */
/************************************************************************/
void
Renderer::InitializeData(GameEngineSettings *gameEngineSettings)
{
    SetWindowData(gameEngineSettings->mWindowWidth,
                  gameEngineSettings->mWindowHeight,
                  gameEngineSettings->mWindowNear,
                  gameEngineSettings->mWindowFar);
    SetViewportData(0.0f, 0.0f,
                    float(gameEngineSettings->mWindowWidth),
                    float(gameEngineSettings->mWindowHeight));

    mBlendStateDefault = make_unique<BlendState>();
    mCullStateDefault = make_unique<CullState>();
    mDepthTestStateDefault = make_unique<DepthTestState>();
    mOffsetStateDefault = make_unique<OffsetState>();
    mStencilTestStateDefault = make_unique<StencilTestState>();
    mWireframeStateDefault = make_unique<WireframeState>();

    mBlendStateCurrent = mBlendStateDefault.get();
    mCullStateCurrent = mCullStateDefault.get();
    mDepthTestStateCurrent = mDepthTestStateDefault.get();
    mOffsetStateCurrent = mOffsetStateDefault.get();
    mStencilTestStateCurrent = mStencilTestStateDefault.get();
    mWireframeStateCurrent = mWireframeStateDefault.get();
}

void
Renderer::DestroyData()
{
}

/************************************************************************/
/* Viewport Management                                                  */
/************************************************************************/
const Viewport *
Renderer::GetViewport() const
{
    return &mViewport;
}

void
Renderer::SetViewportData(float x, float y, float width, float height)
{
    if (mWindowInitialized)
    {
        mViewport.Set(x, y, x + width, y + height, mWindow.mNear, mWindow.mFar);
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Need to initialize window first.")
    }
}

const Window *
Renderer::GetWindow() const
{
    return &mWindow;
}

void
Renderer::SetWindowData(int width, int height, float near, float far)
{
    mWindow.mWidth = width;
    mWindow.mHeight = height;
    mWindow.mNear = near;
    mWindow.mFar = far;

    mWindowInitialized = true;
}

/************************************************************************/
/* Vertex Buffer Management                                             */
/************************************************************************/
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

    auto iter = mVertexBufferTable.find(vertexBuffer);
    if (iter != mVertexBufferTable.end())
    {
        auto vertexBufferPlatform = iter->second;

        auto sourceDataByteNum = vertexBuffer->GetDataByteNum();
        auto sourceData = vertexBuffer->GetData();
        auto destinationData = vertexBufferPlatform->Map(BufferAccessMode::Write);
        memcpy(destinationData, sourceData, sourceDataByteNum);

        vertexBufferPlatform->Unmap();
    }
    else
    {
        auto vertexBufferPlatform = new PlatformVertexBuffer(vertexBuffer);
        mVertexBufferTable[vertexBuffer] = vertexBufferPlatform;
    }
}

/************************************************************************/
/* Vertex Format Management                                             */
/************************************************************************/
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

/************************************************************************/
/* Vertex Group Management                                              */
/************************************************************************/
void
Renderer::Enable(const VertexGroup *vertexGroup)
{
    for (const auto& vertexBindingBufferPair : vertexGroup->mVertexBufferTable)
    {
        auto const & vertexBufferBinding = vertexBindingBufferPair.second;

        Enable(vertexBufferBinding.GetBuffer(),
               vertexBufferBinding.GetIndex(),
               vertexBufferBinding.GetOffset(),
               vertexBufferBinding.GetStride());
    }
}

void
Renderer::Disable(const VertexGroup *vertexGroup)
{
    for (const auto& vertexBindingBufferPair : vertexGroup->mVertexBufferTable)
    {
        auto const & vertexBufferBinding = vertexBindingBufferPair.second;

        Disable(vertexBufferBinding.GetBuffer(),
                vertexBufferBinding.GetIndex());
    }
}

/************************************************************************/
/* Index Buffer Management                                              */
/************************************************************************/
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

    auto iter = mIndexBufferTable.find(indexBuffer);
    if (iter != mIndexBufferTable.end())
    {
        auto indexBufferPlatform = iter->second;

        auto sourceDataByteNum = indexBuffer->GetDataByteNum();
        auto *sourceData = indexBuffer->GetData();
        void *destinationData = indexBufferPlatform->Map(BufferAccessMode::Write);
        memcpy(destinationData, sourceData, sourceDataByteNum);

        indexBufferPlatform->Unmap();
    }
    else
    {
        auto indexBufferPlatform = new PlatformIndexBuffer(indexBuffer);
        mIndexBufferTable[indexBuffer] = indexBufferPlatform;
    }
}

/************************************************************************/
/* Texture Management                                                   */
/************************************************************************/
void
Renderer::Enable(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    switch (texture->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
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
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

void
Renderer::Disable(int textureUnit, const Texture *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    switch (texture->mType)
    {
    case TextureType::None:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    case TextureType::Texture1d:
        Disable(textureUnit, reinterpret_cast<const Texture1d *>(texture));
        break;
    case TextureType::Texture2d:
        Disable(textureUnit, reinterpret_cast<const Texture2d *>(texture));
        break;
    case TextureType::Texture2dArray:
        Disable(textureUnit, reinterpret_cast<const Texture2dArray *>(texture));
        break;
    case TextureType::Texture3d:
        Disable(textureUnit, reinterpret_cast<const Texture3d *>(texture));
        break;
    case TextureType::TextureCube:
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
        break;
    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

void
Renderer::Bind(const Texture1d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Unbind(const Texture1d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Enable(int textureUnit, const Texture1d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture1dTable.find(texture);
    PlatformTexture1d *texturePlatform;
    if (iter != mTexture1dTable.end())
    {
        texturePlatform = iter->second;
    }
    else
    {
        texturePlatform = new PlatformTexture1d(texture);
        mTexture1dTable[texture] = texturePlatform;
    }

    texturePlatform->Enable(textureUnit);
}

void
Renderer::Disable(int textureUnit, const Texture1d *texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture1dTable.find(texture);
    if (iter != mTexture1dTable.end())
    {
        auto texturePlatform = iter->second;
        texturePlatform->Disable(textureUnit);
    }
}

void *
Renderer::Map(const Texture1d *texture, int mipmapLevel, BufferAccessMode mode)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture1dTable.find(texture);
    PlatformTexture1d *texturePlatform;
    if (iter != mTexture1dTable.end())
    {
        texturePlatform = iter->second;
    }
    else
    {
        texturePlatform = new PlatformTexture1d(texture);
        mTexture1dTable[texture] = texturePlatform;
    }

    return texturePlatform->Map(mipmapLevel, mode);
}

void
Renderer::Unmap(const Texture1d *texture, int mipmapLevel)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    auto iter = mTexture1dTable.find(texture);
    if (iter != mTexture1dTable.end())
    {
        auto texturePlatform = iter->second;
        texturePlatform->Unmap(mipmapLevel);
    }
}

void
Renderer::Update(const Texture1d *texture, int mipmapLevel)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    // TODO(Wuxiang): Add mipmap support.
    auto iter = mTexture1dTable.find(texture);
    if (iter != mTexture1dTable.end())
    {
        auto texturePlatform = iter->second;

        unsigned char *sourceData = texture->mData;
        void *targetData = texturePlatform->Map(mipmapLevel, BufferAccessMode::Write);
        memcpy(targetData, sourceData, texture->mDataByteNum);
        texturePlatform->Unmap(mipmapLevel);
    }
    else
    {
        auto texturePlatform = new PlatformTexture1d(texture);
        mTexture1dTable[texture] = texturePlatform;
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
    auto iter = mTexture2dTable.find(texture);
    if (iter != mTexture2dTable.end())
    {
        auto texturePlatform = iter->second;

        unsigned char *sourceData = texture->mData;
        void *targetData = texturePlatform->Map(mipmapLevel, BufferAccessMode::Write);
        memcpy(targetData, sourceData, texture->mDataByteNum);
        texturePlatform->Unmap(mipmapLevel);
    }
    else
    {
        auto texturePlatform = new PlatformTexture2d(texture);
        mTexture2dTable[texture] = texturePlatform;
    }
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

void *
Renderer::Map(const Texture2dArray * /* textureArray */, int /* mipmapLevel */, BufferAccessMode /* mode */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Unmap(const Texture2dArray * /* textureArray */, int /* mipmapLevel */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Update(const Texture2dArray * /* textureArray */, int /* mipmapLevel */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Bind(const Texture3d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Unbind(const Texture3d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Enable(int /* textureUnit */, const Texture3d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Disable(int /* textureUnit */, const Texture3d * /* texture */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void *
Renderer::Map(const Texture3d * /* texture */, int /* mipmapLevel */, BufferAccessMode /* mode */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Unmap(const Texture3d * /* texture */, int /* mipmapLevel */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

void
Renderer::Update(const Texture3d * /* texture */, int /* mipmapLevel */)
{
    FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
}

/************************************************************************/
/* Sampler Management                                                   */
/************************************************************************/
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

/************************************************************************/
/* Shader Management                                                   */
/************************************************************************/
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

/************************************************************************/
/* Pass Management                                                      */
/************************************************************************/
void
Renderer::Enable(const VisualEffectPass *pass)
{
    // Set pass' render states.
    SetBlendStatePlatform(pass->GetBlendState());
    SetCullStatePlatform(pass->GetCullState());
    SetDepthTestStatePlatform(pass->GetDepthTestState());
    SetOffsetStatePlatform(pass->GetOffsetState());
    SetStencilTestStatePlatform(pass->GetStencilTestState());
    SetWireframeStatePlatform(pass->GetWireframeState());
}

void
Renderer::Disable(const VisualEffectPass * /* pass */)
{
}

void
Renderer::Enable(const VisualEffectInstancePass *pass, const Camera *camera, const Visual *visual)
{
    FALCON_ENGINE_CHECK_NULLPTR(pass);

    // Enable required shader textures.
    for (auto textureIter = pass->GetShaderTextureBegin(); textureIter != pass->GetShaderTextureEnd(); ++textureIter)
    {
        Enable(textureIter->first, textureIter->second);
    }

    // Enable required shader samplers.
    for (auto samplerIter = pass->GetShaderSamplerBegin(); samplerIter != pass->GetShaderSamplerEnd(); ++samplerIter)
    {
        Enable(samplerIter->first, samplerIter->second);
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
        Update(pass, uniform, camera, visual);
    }
}

void
Renderer::Disable(const VisualEffectInstancePass *pass)
{
    FALCON_ENGINE_CHECK_NULLPTR(pass);

    // Disable required shader textures.
    for (auto textureIter = pass->GetShaderTextureBegin(); textureIter != pass->GetShaderTextureEnd(); ++textureIter)
    {
        Disable(textureIter->first, textureIter->second);
    }

    // Disable required shader samplers.
    for (auto samplerIter = pass->GetShaderSamplerBegin(); samplerIter != pass->GetShaderSamplerEnd(); ++samplerIter)
    {
        Disable(samplerIter->first, samplerIter->second);
    }
}

void
Renderer::Update(const VisualEffectInstancePass *pass, ShaderUniform *uniform, const Camera *camera, const Visual *visual)
{
    // Update uniform state and location
    if (uniform->mLocation == 0)
    {
        auto shader = pass->GetShader();
        uniform->mEnabled = shader->IsUniformEnabled(uniform->mName);
        uniform->mLocation = shader->GetUniformLocation(uniform->mName);
    }

    // Update uniform value
    if (uniform->mEnabled)
    {
        uniform->Update(camera, visual);
    }

    // Update uniform value in context.
    if (uniform->mUpdated)
    {
        PlatformShaderUniform::UpdateContext(uniform);
    }
}

/************************************************************************/
/* Draw                                                                 */
/************************************************************************/
void
Renderer::Draw(
    _IN_     const Camera *camera,
    _IN_OUT_ Visual       *visual)
{
    // NOTE(Wuxiang): We don't need to check the camera is not null here, because
    // certain rendering task won't need camera information.

    FALCON_ENGINE_CHECK_NULLPTR(visual);

    visual->ForEffectInstance([ = ](std::shared_ptr<VisualEffectInstance> visualEffectInstance)
    {
        // NOTE(Wuxiang): The visual instance is guaranteed to not be null.
        FALCON_ENGINE_CHECK_NULLPTR(visualEffectInstance);

        Draw(camera, visual, visualEffectInstance.get());
    });
}

void
Renderer::Draw(
    _IN_     const Camera         *camera,
    _IN_     const Visual         *visual,
    _IN_OUT_ VisualEffectInstance *visualEffectInstance)
{
    // NOTE(Wuxiang): The non-constness of instance comes from the fact that
    // during the binding of shader, the renderer would look up the shader's
    // location for each vertex attribute and each uniform.

    FALCON_ENGINE_CHECK_NULLPTR(visual);
    FALCON_ENGINE_CHECK_NULLPTR(visualEffectInstance);

    // NOTE(Wuxiang): The order of enabling resource depends on the how fast
    // context would switch those resources.

    // NOTE(Wuxiang): Currently this function assume that all passes are using
    // same vertex attribute array, so that we don't switch vertex format between
    // the shader.

    // TODO(Wuxiang): 2017-05-22 14:16. Dirty Flag and Sorting.

    auto visualEffect = visualEffectInstance->GetEffect();

    // Enable vertex attribute array.
    auto vertexFormat = visual->GetVertexFormat();
    Enable(vertexFormat);

    // Enable vertex group and consequently vertex buffer.
    auto vertexGroup = visual->GetVertexGroup();
    Enable(vertexGroup);

    auto primitive = visual->GetMesh()->GetPrimitive();
    auto indexBuffer = primitive->GetIndexBuffer();
    if (indexBuffer)
    {
        // Enable index buffer.
        Enable(indexBuffer);
    }

    const int passNum = visualEffectInstance->GetPassNum();
    for (int passIndex = 0; passIndex < passNum; ++passIndex)
    {
        auto visualEffectInstancePass = visualEffectInstance->GetPass(passIndex);

        // Enable shader.
        auto shader = visualEffectInstancePass->GetShader();
        Enable(shader);

        // Enable effect instance pass.
        Enable(visualEffectInstancePass, camera, visual);

        // Enable effect pass.
        auto visualEffectPass = visualEffect->GetPass(passIndex);
        Enable(visualEffectPass);

        // Draw primitive.
        auto primitiveInstancingNum = visualEffectInstancePass->GetShaderInstancingNum();
        DrawPrimitivePlatform(primitive, primitiveInstancingNum);

        // Disable effect pass.
        Disable(visualEffectPass);

        // Disable effect instance pass.
        Disable(visualEffectInstancePass);

        // Disable the shader.
        Disable(shader);
    }

    // Disable index buffer.
    if (indexBuffer)
    {
        Disable(indexBuffer);
    }

    // Disable vertex buffer.
    Disable(vertexGroup);

    // Disable vertex attribute array.
    Disable(vertexFormat);
}

}
