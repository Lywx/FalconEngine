#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <map>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Viewport.h>
#include <FalconEngine/Graphics/Renderer/Window.h>

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
class ShaderUniform;
class Visual;
class VisualEffectInstance;
class VisualEffectInstancePass;
class VisualEffectPass;

/************************************************************************/
/* Renderer Resource                                                    */
/************************************************************************/
class Buffer;
enum class BufferAccessMode;
enum class BufferFlushMode;
enum class BufferSynchronizationMode;
class VertexBuffer;
class VertexFormat;
class VertexGroup;
class IndexBuffer;

class Texture;
class Texture1d;
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
class PlatformIndexBuffer;
class PlatformVertexBuffer;
class PlatformVertexFormat;
class PlatformTexture1d;
class PlatformTexture2d;
class PlatformTexture2dArray;
class PlatformTexture3d;
class PlatformSampler;

/************************************************************************/
/* Platform Rendering Pipeline                                          */
/************************************************************************/
class PlatformShader;
class PlatformRendererData;
class PlatformRendererDataDeleter
{
public:
    void operator()(PlatformRendererData *rendererData);
};

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Renderer final
{
public:
    /************************************************************************/
    /* Platform Independent Members                                         */
    /************************************************************************/
    static Renderer *
    GetInstance()
    {
        static Renderer sInstance;
        return &sInstance;
    }

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
    InitializeData();

    void
    DestroyData();

public:
    /************************************************************************/
    /* Viewport Management                                                  */
    /************************************************************************/
    const Viewport *
    GetViewport() const;

    // @note The viewport is specified in right-handed screen
    // coordinates. The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    void
    SetViewportData(float x, float y, float width, float height);

    const Window *
    GetWindow() const;

    void
    SetWindowData(int width, int height, float near, float far);

public:
    /************************************************************************/
    /* Universal Buffer Management                                          */
    /************************************************************************/
    void *
    Map(const Buffer             *buffer,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const Buffer *buffer);

    void
    Update(const Buffer             *buffer,
           BufferAccessMode          access,
           BufferFlushMode           flush,
           BufferSynchronizationMode synchronization);

    /************************************************************************/
    /* Vertex Buffer Management                                             */
    /************************************************************************/
    void
    Bind(const VertexBuffer *vertexBuffer);

    void
    Unbind(const VertexBuffer *vertexBuffer);

    // @param offset - offset into the first data in byte.
    // @param stride - stride between contiguous data in byte.
    void
    Enable(const VertexBuffer *vertexBuffer, int bindingIndex, int64_t offset, int stride);

    void
    Disable(const VertexBuffer *vertexBuffer, int bindingIndex);

    void *
    Map(const VertexBuffer       *vertexBuffer,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const VertexBuffer *vertexBuffer);

    void
    Flush(VertexBuffer *vertexBuffer,
          int64_t       offset,
          int64_t       size);

    /************************************************************************/
    /* Vertex Format Management                                             */
    /************************************************************************/
    void
    Bind(const VertexFormat *vertexFormat);

    void
    Unbind(const VertexFormat *vertexFormat);

    void
    Enable(const VertexFormat *vertexFormat);

    void
    Disable(const VertexFormat *vertexFormat);

    /************************************************************************/
    /* Vertex Group Management                                              */
    /************************************************************************/
    void
    Enable(const VertexGroup *vertexGroup);

    void
    Disable(const VertexGroup *vertexGroup);

    /************************************************************************/
    /* Index Buffer Management                                              */
    /************************************************************************/
    void
    Bind(const IndexBuffer *indexBuffer);

    void
    Unbind(const IndexBuffer *indexBuffer);

    void
    Enable(const IndexBuffer *indexBuffer);

    void
    Disable(const IndexBuffer *indexBuffer);

    void *
    Map(const IndexBuffer        *indexBuffer,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const IndexBuffer *indexBuffer);

    /************************************************************************/
    /* Universal Texture Management                                         */
    /************************************************************************/
    // @summary Provide a uniform interface for all texture.
    void
    Enable(int textureUnit, const Texture *texture);

    // @summary Provide a uniform interface for all texture.
    void
    Disable(int textureUnit, const Texture *texture);

    // NEW(Wuxiang): Add the ability of reading back texture.
    // NOTE(Wuxiang): But I don't know why I need any function to update texture.

    /************************************************************************/
    /* Texture 1D Management                                                */
    /************************************************************************/
    void
    Bind(const Texture1d *texture);

    void
    Unbind(const Texture1d *texture);

    void
    Enable(int textureUnit, const Texture1d *texture);

    void
    Disable(int textureUnit, const Texture1d *texture);

    void *
    Map(const Texture1d          *texture,
        int                       mipmapLevel,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const Texture1d *texture, int mipmapLevel);

    /************************************************************************/
    /* Texture 2D Management                                                */
    /************************************************************************/
    void
    Bind(const Texture2d *texture);

    void
    Unbind(const Texture2d *texture);

    void
    Enable(int textureUnit, const Texture2d *texture);

    void
    Disable(int textureUnit, const Texture2d *texture);

    void *
    Map(const Texture2d          *texture,
        int                       mipmapLevel,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const Texture2d *texture, int mipmapLevel);

    /************************************************************************/
    /* Texture 2D Array Management                                          */
    /************************************************************************/
    void
    Bind(const Texture2dArray *textureArray);

    void
    Unbind(const Texture2dArray *textureArray);

    void
    Enable(int                   textureUnit,
           const Texture2dArray *textureArray);

    void
    Disable(int                   textureUnit,
            const Texture2dArray *textureArray);

    void *
    Map(const Texture2dArray     *textureArray,
        int                       textureIndex,
        int                       mipmapLevel,
        BufferAccessMode          access,
        BufferFlushMode           flush,
        BufferSynchronizationMode synchronization,
        int64_t                   offset,
        int64_t                   size);

    void
    Unmap(const Texture2dArray *textureArray,
          int                   textureIndex,
          int                   mipmapLevel);

    /************************************************************************/
    /* Texture 3D Management                                                */
    /************************************************************************/
    void
    Bind(const Texture3d *texture);

    void
    Unbind(const Texture3d *texture);

    void
    Enable(int textureUnit, const Texture3d *texture);

    void
    Disable(int textureUnit, const Texture3d *texture);

    void *
    Map(const Texture3d *texture, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(const Texture3d *texture, int mipmapLevel);

    void
    Update(const Texture3d *texture, int mipmapLevel);

    /************************************************************************/
    /* Sampler Management                                                   */
    /************************************************************************/
    void
    Bind(const Sampler *sampler);

    void
    Unbind(const Sampler *sampler);

    void
    Enable(int textureUnit, const Sampler *sampler);

    void
    Disable(int textureUnit, const Sampler *sampler);

    /************************************************************************/
    /* Shader Management                                                   */
    /************************************************************************/
    void
    Bind(Shader *shader);

    void
    Unbind(const Shader *shader);

    void
    Enable(Shader *shader);

    void
    Disable(const Shader *shader);

    /************************************************************************/
    /* Pass Management                                                      */
    /************************************************************************/
    void
    Enable(const VisualEffectPass *pass);

    void
    Enable(const VisualEffectInstancePass *pass, const Camera *camera, const Visual *visual);

    // @summary Update effect instance's uniform.
    void
    Update(const VisualEffectInstancePass *pass, ShaderUniform *uniform, const Camera *camera, const Visual *visual);

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    // @summary Draw single instance of visual.
    void
    Draw(const Camera *camera, const Visual *visual);

    // @summary Draw single instance of visual.
    void
    Draw(const Camera *camera, const Visual *visual, VisualEffectInstance *visualEffectInstance);

private:
    /************************************************************************/
    /* Platform Hash Table                                                  */
    /************************************************************************/
    std::map<const IndexBuffer *, PlatformIndexBuffer *>       mIndexBufferTable;
    std::map<const VertexBuffer *, PlatformVertexBuffer *>     mVertexBufferTable;
    std::map<const VertexFormat *, PlatformVertexFormat *>     mVertexFormatTable;

    std::map<const Shader *, PlatformShader *>                 mShaderTable;
    std::map<const Sampler *, PlatformSampler *>               mSamplerTable;
    std::map<const Texture1d *, PlatformTexture1d *>           mTexture1dTable;
    std::map<const Texture2d *, PlatformTexture2d *>           mTexture2dTable;
    std::map<const Texture2dArray *, PlatformTexture2dArray *> mTexture2dArrayTable;

    /************************************************************************/
    /* Dirty Flags                                                          */
    /************************************************************************/
    const IndexBuffer             *mIndexBufferPrevious;
    const VertexGroup             *mVertexGroupPrevious;
    const VertexFormat            *mVertexFormatPrevious;

    const VisualEffectPass        *mPassPrevious;

    Shader                        *mShaderPrevious;
    std::map<int, const Sampler *> mSamplerPrevious;
    std::map<int, const Texture *> mTexturePrevious;

    /************************************************************************/
    /* Renderer State                                                       */
    /************************************************************************/
    std::unique_ptr<BlendState>       mBlendStateDefault;
    std::unique_ptr<CullState>        mCullStateDefault;
    std::unique_ptr<DepthTestState>   mDepthTestStateDefault;
    std::unique_ptr<OffsetState>      mOffsetStateDefault;
    std::unique_ptr<StencilTestState> mStencilTestStateDefault;
    std::unique_ptr<WireframeState>   mWireframeStateDefault;

    const BlendState                 *mBlendStateCurrent;
    const CullState                  *mCullStateCurrent;
    const DepthTestState             *mDepthTestStateCurrent;
    const OffsetState                *mOffsetStateCurrent;
    const StencilTestState           *mStencilTestStateCurrent;
    const WireframeState             *mWireframeStateCurrent;

    Viewport                          mViewport;
    Window                            mWindow;
    bool                              mWindowInitialized = false;
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
    DestroyPlatform();

    /************************************************************************/
    /* State Management                                                     */
    /************************************************************************/
    void
    SetBlendStatePlatform(const BlendState *blendState);

    void
    SetCullStatePlatform(const CullState *cullState);

    void
    SetDepthTestStatePlatform(const DepthTestState *depthTestState);

    void
    SetOffsetStatePlatform(const OffsetState *offsetState);

    void
    SetStencilTestStatePlatform(const StencilTestState *stencilTestState);

    void
    SetWireframeStatePlatform(const WireframeState *wireframeState);

public:
    /************************************************************************/
    /* Viewport Management                                                  */
    /************************************************************************/
    // @note The viewport is specified in right-handed screen
    // coordinates. The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    void
    SetViewportPlatform(float x, float y, float width, float height);

    void
    SetWindowPlatform(int width, int height, float near, float far);

public:
    /************************************************************************/
    /* Default Framebuffer Management                                       */
    /************************************************************************/
    void
    ClearColorBufferPlatform(Vector4f color);

    void
    ClearDepthBufferPlatform(float depth);

    void
    ClearStencilBufferPlatform(unsigned int stencil);

    void
    ClearFrameBufferPlatform(Vector4f color, float depth, unsigned int stencil);

    void
    SwapFrameBufferPlatform();

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    void
    DrawPrimitivePlatform(const Primitive *primitive, int instancingNum);

private:
    std::unique_ptr<PlatformRendererData, PlatformRendererDataDeleter> mData;
    bool                                                               mDataInitialized = false;
};
#pragma warning(default: 4251)

}
