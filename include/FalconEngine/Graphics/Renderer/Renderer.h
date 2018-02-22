#pragma once

#include <FalconEngine/Core/Macro.h>

#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Renderer/Viewport.h>
#include <FalconEngine/Graphics/Renderer/Window.h>
#include <FalconEngine/Graphics/Renderer/Resource/TextureBinding.h>

namespace FalconEngine
{
/************************************************************************/
/* Engine Resource                                                      */
/************************************************************************/
class GameEngineData;
class GameEngineSettings;

/************************************************************************/
/* Rendering Pipeline                                                   */
/************************************************************************/
class Camera;
class Font;
class FontText;
class Primitive;
class Shader;
class Uniform;
class UniformBuffer;
class UniformBufferBinding;
class Visual;
class VisualEffectInstance;
class VisualEffectInstancePass;
class VisualEffectPass;

/************************************************************************/
/* Renderer Resource                                                    */
/************************************************************************/
class Buffer;
enum class ResourceMapAccessMode;
enum class ResourceMapFlushMode;
enum class ResourceMapSyncMode;
class IndexBuffer;
class ShaderBuffer;
class VertexBuffer;
class VertexFormat;
class VertexGroup;

class Texture;
class Texture1d;
class Texture1dArray;
class Texture2d;
class Texture2dArray;
class Texture3d;
class Sampler;

/************************************************************************/
/* Renderer States                                                      */
/************************************************************************/
class BlendState;
class OffsetState;
class BlendState;
class CullState;
class DepthTestState;
class OffsetState;
class StencilTestState;
class WireframeState;

/************************************************************************/
/* Platform Renderer Resource                                           */
/************************************************************************/
class PlatformShaderBuffer;
class PlatformIndexBuffer;
class PlatformUniformBuffer;
class PlatformVertexBuffer;
class PlatformVertexFormat;
class PlatformTexture1d;
class PlatformTexture1dArray;
class PlatformTexture2d;
class PlatformTexture2dArray;
class PlatformTexture3d;
class PlatformSampler;

/************************************************************************/
/* Platform Rendering Pipeline                                          */
/************************************************************************/
class PlatformShader;
class PlatformRendererData;
FALCON_ENGINE_DELETER_DECLARE(PlatformRendererData, PlatformRendererDataDeleter);
class PlatformRendererState;
FALCON_ENGINE_DELETER_DECLARE(PlatformRendererState, PlatformRendererStateDeleter);

FALCON_ENGINE_CLASS_BEGIN Renderer final
{
    /************************************************************************/
    /* Platform Independent Members                                         */
    /************************************************************************/

    FALCON_ENGINE_SINGLETON_SAFE_DECLARE(Renderer);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    Renderer();

public:
    ~Renderer();

    /************************************************************************/
    /* Initialization and Destroy                                           */
    /************************************************************************/
public:
    void
    Initialize();

private:
    void
    DestroyData();

    void
    DestroyResource();

    void
    InitializeData();

public:
    /************************************************************************/
    /* Framebuffer Management                                               */
    /************************************************************************/
    void
    ClearColorBuffer(const Vector4f & color);

    void
    ClearDepthBuffer(float depth);

    void
    ClearStencilBuffer(unsigned int stencil);

    void
    ClearFrameBuffer(const Vector4f & color, float depth, unsigned int stencil);

    /************************************************************************/
    /* Viewport Management                                                  */
    /************************************************************************/
    const Viewport *
    GetViewport() const;

    // @note You aren't allowed to change near and far of the viewport.
    void
    SetViewport(float x, float y, float width, float height);

private:
    // @note The viewport is specified in right-handed screen
    // coordinates. The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    //
    // @note You aren't allowed to change near and far of the viewport.
    void
    SetViewportData(float x, float y, float width, float height, float near, float far);

public:
    const Window *
    GetWindow() const;

    void
    SetWindow(int width, int height, float near, float far);

private:
    void
    SetWindowData(int width, int height, float near, float far);

public:
    /************************************************************************/
    /* Universal Buffer Management                                          */
    /************************************************************************/
    // NOTE(Wuxiang): The Bind / Enable / Disable interface is inconsistent for
    // different buffer type. So the Renderer interface require buffer to use
    // derived buffer class to access corresponding functionality.
    void
    Unbind(const Buffer * buffer);

    void *
    Map(const Buffer * buffer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const Buffer * buffer);

    void
    Flush(const Buffer * buffer,
          int64_t offset,
          int64_t size);

    void
    Update(const Buffer * buffer,
           ResourceMapAccessMode access,
           ResourceMapFlushMode flush,
           ResourceMapSyncMode sync);

    /************************************************************************/
    /* Index Buffer Management                                              */
    /************************************************************************/
    void
    Bind(const IndexBuffer * indexBuffer);

    void
    Unbind(const IndexBuffer * indexBuffer);

    void
    Enable(const IndexBuffer * indexBuffer);

    void
    Disable(const IndexBuffer * indexBuffer);

    void *
    Map(const IndexBuffer * indexBuffer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const IndexBuffer * indexBuffer);

    void
    Flush(const IndexBuffer * indexBuffer,
          int64_t offset,
          int64_t size);

    /************************************************************************/
    /* Shader Buffer Management                                             */
    /************************************************************************/
    void
    Bind(const ShaderBuffer * shaderBuffer);

    void
    Unbind(const ShaderBuffer * shaderBuffer);

    void
    Enable(const ShaderBuffer * shaderBuffer, unsigned int bindingIndex);

    void
    Disable(const ShaderBuffer * shaderBuffer);

    void *
    Map(const ShaderBuffer * shaderBuffer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const ShaderBuffer * shaderBuffer);

    void
    Flush(const ShaderBuffer * shaderBuffer,
          int64_t offset,
          int64_t size);

    /************************************************************************/
    /* Uniform Buffer Management                                            */
    /************************************************************************/
    void
    Bind(const UniformBuffer * uniformBuffer);

    void
    Unbind(const UniformBuffer * uniformBuffer);

    void
    Enable(const UniformBuffer * uniformBuffer, unsigned int bindingIndex, unsigned int shaderMask);

    void
    Disable(const UniformBuffer * uniformBuffer, unsigned int bindingIndex, unsigned int shaderMask);

    void *
    Map(const UniformBuffer * uniformBuffer);

    void *
    Map(const UniformBuffer * uniformBuffer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const UniformBuffer * uniformBuffer);

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    void
    Bind(const VertexBuffer * vertexBuffer);

    void
    Unbind(const VertexBuffer * vertexBuffer);

    // @param offset - offset into the first data in byte.
    // @param stride - stride between contiguous data in byte.
    void
    Enable(const VertexBuffer * vertexBuffer,
           unsigned int        bindingIndex,
           int64_t             offset,
           int                 stride);

    void
    Disable(const VertexBuffer * vertexBuffer, unsigned int bindingIndex);

    void *
    Map(const VertexBuffer * vertexBuffer,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const VertexBuffer * vertexBuffer);

    void
    Flush(const VertexBuffer * vertexBuffer, int64_t offset, int64_t size);

    /************************************************************************/
    /* Vertex Format Management                                             */
    /************************************************************************/
    void
    Bind(const VertexFormat * vertexFormat);

    void
    Unbind(const VertexFormat * vertexFormat);

    void
    Enable(const VertexFormat * vertexFormat);

    void
    Disable(const VertexFormat * vertexFormat);

    /************************************************************************/
    /* Vertex Group Management                                              */
    /************************************************************************/
    void
    Enable(const VertexGroup * vertexGroup);

    void
    Disable(const VertexGroup * vertexGroup);

    /************************************************************************/
    /* Universal Texture Management                                         */
    /************************************************************************/
    void
    Bind(const Texture * texture);

    void
    Unbind(const Texture * texture);

    // @summary Provide a uniform interface for all texture.
    void
    Enable(int textureUnit,
           const Texture * texture,
           const TextureShaderMaskList & textureShaderMaskList);

    // @summary Provide a uniform interface for all texture.
    void
    Disable(int textureUnit,
            const Texture * texture,
            const TextureShaderMaskList & textureShaderMaskList);

    // NEW(Wuxiang): Add the ability of reading back texture.
    // NOTE(Wuxiang): But I don't know why I need any function to update texture.

    /************************************************************************/
    /* Texture 1D Management                                                */
    /************************************************************************/
    PlatformTexture1d *
    Get(const Texture1d * texture);

    void
    Bind(const Texture1d * texture);

    void
    Unbind(const Texture1d * texture);

    void
    Enable(int textureUnit,
           const Texture1d * texture,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(int textureUnit,
            const Texture1d * texture,
            const TextureShaderMaskList & textureShaderMaskList);

    void *
    Map(const Texture1d * texture,
        int mipmapLevel,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const Texture1d * texture, int mipmapLevel);

    /************************************************************************/
    /* Texture 1D Array Management                                          */
    /************************************************************************/
    PlatformTexture1dArray *
    Get(const Texture1dArray * textureArray);

    void
    Bind(const Texture1dArray * textureArray);

    void
    Unbind(const Texture1dArray * textureArray);

    void
    Enable(int textureUnit,
           const Texture1dArray * textureArray,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(int textureUnit,
            const Texture1dArray * textureArray,
            const TextureShaderMaskList & textureShaderMaskList);

    void *
    Map(const Texture1dArray * textureArray,
        int textureIndex,
        int mipmapLevel,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const Texture1dArray * textureArray,
          int textureIndex,
          int mipmapLevel);

    /************************************************************************/
    /* Texture 2D Management                                                */
    /************************************************************************/
    PlatformTexture2d *
    Get(const Texture2d * texture);

    void
    Bind(const Texture2d * texture);

    void
    Unbind(const Texture2d * texture);

    void
    Enable(int textureUnit,
           const Texture2d * texture,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(int textureUnit,
            const Texture2d * texture,
            const TextureShaderMaskList & textureShaderMaskList);

    void *
    Map(const Texture2d * texture,
        int mipmapLevel,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const Texture2d * texture, int mipmapLevel);

    /************************************************************************/
    /* Texture 2D Array Management                                          */
    /************************************************************************/
    PlatformTexture2dArray *
    Get(const Texture2dArray * textureArray);

    void
    Bind(const Texture2dArray * textureArray);

    void
    Unbind(const Texture2dArray * textureArray);

    void
    Enable(int textureUnit,
           const Texture2dArray * textureArray,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(int textureUnit,
            const Texture2dArray * textureArray,
            const TextureShaderMaskList & textureShaderMaskList);

    void *
    Map(const Texture2dArray * textureArray,
        int textureIndex,
        int mipmapLevel,
        ResourceMapAccessMode access,
        ResourceMapFlushMode flush,
        ResourceMapSyncMode sync,
        int64_t offset,
        int64_t size);

    void
    Unmap(const Texture2dArray * textureArray,
          int textureIndex,
          int mipmapLevel);

    /************************************************************************/
    /* Texture 3D Management                                                */
    /************************************************************************/
    PlatformTexture3d *
    Get(const Texture3d * texture);

    void
    Bind(const Texture3d * texture);

    void
    Unbind(const Texture3d * texture);

    void
    Enable(int textureUnit,
           const Texture3d * texture,
           const TextureShaderMaskList & textureShaderMaskList);

    void
    Disable(int textureUnit,
            const Texture3d * texture,
            const TextureShaderMaskList & textureShaderMaskList);

    /************************************************************************/
    /* Sampler Management                                                   */
    /************************************************************************/
    void
    Bind(const Sampler * sampler);

    void
    Unbind(const Sampler * sampler);

    void
    Enable(int textureUnit,
           const Sampler * sampler,
           unsigned int samplerShaderMask);

    void
    Disable(int textureUnit,
            const Sampler * sampler,
            unsigned int samplerShaderMask);

    /************************************************************************/
    /* Shader Management                                                   */
    /************************************************************************/
    PlatformShader *
    Get(const Shader * shader);

    void
    Bind(Shader * shader);

    void
    Unbind(const Shader * shader);

    void
    Enable(Shader * shader);

    void
    Disable(const Shader * shader);

    /************************************************************************/
    /* Pass Management                                                      */
    /************************************************************************/
    void
    Enable(VisualEffectPass * pass);

    void
    Enable(VisualEffectInstancePass * pass,
           const Camera * camera,
           const Visual * visual);

    // @summary Update effect instance's uniform.
    void
    Update(const VisualEffectInstancePass * pass,
           Uniform * uniform,
           const Camera * camera,
           const Visual * visual);

    void
    Update(const VisualEffectInstancePass * pass,
           UniformBufferBinding * uniformBufferBinding,
           const Camera * camera,
           const Visual * visual);

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    // @summary Draw single instance of visual.
    void
    Draw(const Camera * camera, const Visual * visual);

    // @summary Draw single instance of visual.
    void
    Draw(const Camera * camera, const Visual * visual, VisualEffectInstance * visualEffectInstance);

private:
    /************************************************************************/
    /* Platform Resource Table                                              */
    /************************************************************************/
    // NOTE(Wuxiang): The reason I choose to use std::map here is that the element
    // number is relatively small to a point that the performance gain is not
    // significant.
    std::map<const IndexBuffer *, PlatformIndexBuffer *> mIndexBufferTable;
    std::map<const ShaderBuffer *, PlatformShaderBuffer *> mShaderBufferTable;
    std::map<const UniformBuffer *, PlatformUniformBuffer *> mUniformBufferTable;
    std::map<const VertexBuffer *, PlatformVertexBuffer *> mVertexBufferTable;
    std::map<const VertexFormat *, PlatformVertexFormat *> mVertexFormatTable;
    std::map<const Shader *, PlatformShader *> mShaderTable;
    std::map<const Sampler *, PlatformSampler *> mSamplerTable;
    std::map<const Texture1d *, PlatformTexture1d *> mTexture1dTable;
    std::map<const Texture1dArray *, PlatformTexture1dArray *> mTexture1dArrayTable;
    std::map<const Texture2d *, PlatformTexture2d *> mTexture2dTable;
    std::map<const Texture2dArray *, PlatformTexture2dArray *> mTexture2dArrayTable;

    /************************************************************************/
    /* Dirty Flags                                                          */
    /************************************************************************/
    const IndexBuffer *mIndexBufferPrevious;
    const ShaderBuffer *mShaderBufferPrevious;
    const VertexGroup *mVertexGroupPrevious;
    const VertexFormat *mVertexFormatPrevious;
    const VisualEffectPass *mPassPrevious;
    Shader *mShaderPrevious;

    // Sampler table indexed by texture binding index.
    std::map<int, const Sampler *> mSamplerPrevious;

    // Texture table indexed by texture binding index.
    std::map<int, const Texture *> mTexturePrevious;

    /************************************************************************/
    /* Renderer State                                                       */
    /************************************************************************/
    std::unique_ptr<BlendState> mBlendStateDefault;
    std::unique_ptr<CullState> mCullStateDefault;
    std::unique_ptr<DepthTestState> mDepthTestStateDefault;
    std::unique_ptr<OffsetState> mOffsetStateDefault;
    std::unique_ptr<StencilTestState> mStencilTestStateDefault;
    std::unique_ptr<WireframeState> mWireframeStateDefault;

    // NEW(Wuxiang): The dirty flag pattern here is not very effective. Because
    // most of draw call require different states. Ideally, you should be able to
    // semantically group all the draw call that share the same states into sub
    // render group. This requires some kind of draw command organization.

    // NEW(Wuxiang): You should read "Jason Zink, Matt Pettineo, Jack Hoxley
    // Practical Rendering and Computation with Direct3D 11, 2011" to learn more
    // about the draw state encapsulation (3.3.4 Draw State).

    // NEW(Wuxiang): You should consider implementing the tactics in "Christer
    // Ericson Order Your Graphics Draw Calls Around, 2008".

    const BlendState *mBlendStateCurrent;
    const CullState *mCullStateCurrent;
    const DepthTestState *mDepthTestStateCurrent;
    const OffsetState *mOffsetStateCurrent;
    const StencilTestState *mStencilTestStateCurrent;
    const WireframeState *mWireframeStateCurrent;

    Viewport mViewport;
    Window mWindow;
    bool mWindowInitialized = false;

private:
    /************************************************************************/
    /* Platform Dependent Members                                           */
    /************************************************************************/

    /************************************************************************/
    /* Initialization and Destroy                                           */
    /************************************************************************/
    void
    InitializePlatform();

    void
    InitializeDataPlatform();

    void
    InitializeStatePlatform();

    void
    DestroyPlatform();

public:
    /************************************************************************/
    /* Viewport Management                                                  */
    /************************************************************************/
    // @note The viewport is specified in right-handed screen
    // coordinates. The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    void
    SetViewportPlatform(float x, float y, float width, float height, float near, float far);

    /************************************************************************/
    /* Window Management                                                    */
    /************************************************************************/
    void
    SetWindowPlatform(int width, int height);

public:
    /************************************************************************/
    /* Framebuffer Management                                               */
    /************************************************************************/
    void
    ClearColorBufferPlatform(const Vector4f & color);

    void
    ClearDepthBufferPlatform(float depth);

    void
    ClearStencilBufferPlatform(unsigned int stencil);

    void
    ClearFrameBufferPlatform(const Vector4f & color, float depth, unsigned int stencil);

    void
    RecoverDeviceLostPlatform();

    void
    SwapFrameBufferPlatform();

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    void
    DrawPrimitivePlatform(const Primitive * primitive, int primitiveInstancingNum);

// internal
public:
    std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter>   mData;
    std::unique_ptr<PlatformRendererState, PlatformRendererStateDeleter> mState;
};
FALCON_ENGINE_CLASS_END

}

/************************************************************************/
/* Resource Management Helper                                           */
/************************************************************************/
#define FALCON_ENGINE_RENDERER_BIND(resource) \
static auto sMasterRenderer = FalconEngine::Renderer::GetInstance(); \
sMasterRenderer->Bind(resource);

#define FALCON_ENGINE_RENDERER_UNBIND(resource) \
static auto sMasterRenderer = FalconEngine::Renderer::GetInstance(); \
sMasterRenderer->Unbind(resource);

/************************************************************************/
/* Resource Management Implementation                                   */
/************************************************************************/
#define FALCON_ENGINE_RENDERER_BIND_IMPLEMENT(resource, resourceTable, PlatformResourceKlass) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
if (resourceTable.find(resource) == resourceTable.end()) \
{ \
    resourceTable[resource] = new PlatformResourceKlass(this, resource); \
}

#define FALCON_ENGINE_RENDERER_BIND_FIND(resource, resourceTable, PlatformResourceKlass) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
PlatformResourceKlass *resource##Platform; \
if (iter != resourceTable.end()) \
{ \
    resource##Platform = iter->second; \
} \
else \
{ \
    resource##Platform = new PlatformResourceKlass(this, resource); \
    resourceTable[resource] = resource##Platform; \
} \

#define FALCON_ENGINE_RENDERER_UNBIND_IMPLEMENT(resource, resourceTable) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
if (iter != resourceTable.end()) \
{ \
    auto resource##Platform = iter->second; \
    delete resource##Platform; \
    resourceTable.erase(iter); \
}

#define FALCON_ENGINE_RENDERER_ENABLE_LAZY(resource, resourcePrevious) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
if (resource == resourcePrevious) \
{ \
    return; \
} \
else \
{ \
    if (resourcePrevious) \
    { \
        Disable(resourcePrevious); \
    } \
    resourcePrevious = resource; \
}

#define FALCON_ENGINE_RENDERER_ENABLE_IMPLEMENT(resource, resourceTable, PlatformResourceKlass) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
PlatformResourceKlass *resource##Platform; \
if (iter != resourceTable.end()) \
{ \
    resource##Platform = iter->second; \
} \
else \
{ \
    resource##Platform = new PlatformResourceKlass(this, resource); \
    resourceTable[resource] = resource##Platform; \
} \
\
resource##Platform->Enable(this);

#define FALCON_ENGINE_RENDERER_DISABLE_IMPLEMENT(resource, resourceTable) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
if (iter != resourceTable.end()) \
{ \
    auto resource##Platform = iter->second; \
    resource##Platform->Disable(this); \
}

#define FALCON_ENGINE_RENDERER_MAP_IMPLEMENT(resource, resourceTable, PlatformResourceKlass) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
PlatformResourceKlass *resource##Platform; \
if (iter != resourceTable.end()) \
{ \
    resource##Platform = iter->second; \
} \
else \
{ \
    resource##Platform = new PlatformResourceKlass(this, resource); \
    resourceTable[resource] = resource##Platform; \
} \
\
return resource##Platform->Map(this, access, flush, sync, offset, size);

#define FALCON_ENGINE_RENDERER_UNMAP_IMPLEMENT(resource, resourceTable) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
if (iter != resourceTable.end()) \
{ \
    auto resource##Platform = iter->second; \
    resource##Platform->Unmap(this); \
}

#define FALCON_ENGINE_RENDERER_FLUSH_IMPLEMENT(resource, resourceTable) \
FALCON_ENGINE_CHECK_NULLPTR(resource); \
\
auto iter = resourceTable.find(resource); \
if (iter != resourceTable.end()) \
{ \
    auto resource##Platform = iter->second; \
    resource##Platform->Flush(this, offset, size); \
} \
else \
{ \
    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(std::string("The ") + #resource + " is not mapped before."); \
}

#define FALCON_ENGINE_RENDERER_SET_IMPLEMEN(stateRenderer, state, stateCurrent) \
    FALCON_ENGINE_CHECK_NULLPTR(state); \
    stateCurrent = state; \
    stateRenderer->Set(stateCurrent);

#define FALCON_ENGINE_RENDERER_TEXTURE_ENABLE_LAZY(texture, texturePrevious, textureShaderMask) \
FALCON_ENGINE_CHECK_NULLPTR(texture); \
\
if (texturePrevious[textureUnit] == texture) \
{ \
    return; \
} \
else \
{ \
    if (texturePrevious[textureUnit]) \
    { \
        Disable(textureUnit, texturePrevious[textureUnit], textureShaderMask); \
    } \
\
    texturePrevious[textureUnit] = texture; \
}

#define FALCON_ENGINE_RENDERER_TEXTURE_ENABLE_IMPLEMENT(texture, textureTable, textureShaderMask, PlatformTextureKlass) \
FALCON_ENGINE_CHECK_NULLPTR(texture); \
\
auto iter = textureTable.find(texture); \
PlatformTextureKlass *texture##Platform; \
if (iter != textureTable.end()) \
{ \
    texture##Platform = iter->second; \
} \
else \
{ \
    texture##Platform = new PlatformTextureKlass(this, texture); \
    textureTable[texture] = texture##Platform; \
} \
\
texture##Platform->Enable(this, textureUnit, textureShaderMask);

#define FALCON_ENGINE_RENDERER_TEXTURE_DISABLE_IMPLEMENT(texture, textureTable, textureShaderMask) \
FALCON_ENGINE_CHECK_NULLPTR(texture); \
\
auto iter = textureTable.find(texture); \
if (iter != textureTable.end()) \
{ \
    auto texture##Platform = iter->second; \
    texture##Platform->Disable(this, textureUnit, textureShaderMask); \
}

#define FALCON_ENGINE_RENDERER_TEXTURE_MAP_IMPLEMENT(texture, textureTable, PlatformTextureKlass) \
FALCON_ENGINE_CHECK_NULLPTR(texture); \
\
auto iter = textureTable.find(texture); \
PlatformTextureKlass *texturePlatform; \
if (iter != textureTable.end()) \
{ \
    texturePlatform = iter->second; \
} \
else \
{ \
    texturePlatform = new PlatformTextureKlass(this, texture); \
    textureTable[texture] = texturePlatform; \
} \
\
return texturePlatform->Map(this, access, flush, sync, offset, size);

#define FALCON_ENGINE_RENDERER_TEXTURE_UNMAP_IMPLEMENT(texture, textureTable) \
FALCON_ENGINE_CHECK_NULLPTR(texture); \
\
auto iter = textureTable.find(texture); \
if (iter != textureTable.end()) \
{ \
    auto texturePlatform = iter->second; \
    texturePlatform->Unmap(this); \
}

#define FALCON_ENGINE_RENDERER_TEXTURE_ARRAY_MAP_IMPLEMENT(textureArray, textureArrayTable, textureIndex, PlatformTextureArrayKlass) \
FALCON_ENGINE_CHECK_NULLPTR(textureArray); \
\
auto iter = textureArrayTable.find(textureArray); \
PlatformTextureArrayKlass *textureArrayPlatform; \
if (iter != textureArrayTable.end()) \
{ \
    textureArrayPlatform = iter->second; \
} \
else \
{ \
    textureArrayPlatform = new PlatformTextureArrayKlass(this, textureArray); \
    textureArrayTable[textureArray] = textureArrayPlatform; \
} \
\
return textureArrayPlatform->Map(this, textureIndex, access, flush, sync, offset, size);

#define FALCON_ENGINE_RENDERER_TEXTURE_ARRAY_UNMAP_IMPLEMENT(textureArray, textureArrayTable, textureIndex) \
FALCON_ENGINE_CHECK_NULLPTR(textureArray); \
\
auto iter = textureArrayTable.find(textureArray); \
if (iter != textureArrayTable.end()) \
{ \
    auto textureArrayPlatform = iter->second; \
    textureArrayPlatform->Unmap(this, textureIndex); \
}

#define FALCON_ENGINE_RENDERER_UNBIND_EVERYTHING(resourceTable) \
for (auto iter = resourceTable.begin(); iter != resourceTable.end(); ++iter) \
{ \
    auto resourcePlatform = iter->second; \
    delete resourcePlatform; \
} \
\
resourceTable.clear(); \
