#pragma once

#include <FalconEngine/Graphics/Header.h>

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

/************************************************************************/
/* Rendering Pipeline                                                   */
/************************************************************************/
class BitmapFont;
class BitmapText;
class Camera;
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

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Renderer
{
public:
    /************************************************************************/
    /* Platform Independent Members                                         */
    /************************************************************************/

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Renderer(const GameEngineData *data, int width, int height, float near, float far);
    virtual ~Renderer();

    using PlatformVertexBufferMap   = std::map<const VertexBuffer *, PlatformVertexBuffer *>;
    using PlatformVertexFormatMap   = std::map<const VertexFormat *, PlatformVertexFormat *>;
    using PlatformIndexBufferMap    = std::map<const IndexBuffer *,  PlatformIndexBuffer *>;
    using PlatformTexture1dMap      = std::map<const Texture1d *, PlatformTexture1d *>;
    using PlatformTexture2dMap      = std::map<const Texture2d *, PlatformTexture2d *>;
    using PlatformTexture2dArrayMap = std::map<const Texture2dArray *, PlatformTexture2dArray *>;
    using PlatformTexture3dMap      = std::map<const Texture3d *, PlatformTexture3d *>;
    using PlatformTextureSamplerMap = std::map<const Sampler *, PlatformSampler *>;

    using PlatformShaderMap         = std::map<const Shader *, PlatformShader *>;

private:
    /************************************************************************/
    /* Initialization and Destroy                                           */
    /************************************************************************/
    void
    InitializeExceptPlatform(int width, int height, float near, float far);

    void
    DestroyExceptPlatform();

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
    SetViewportExceptPlatform(float x, float y, float width, float height);

    const Window *
    GetWindow() const;

    void
    SetWindowExceptPlatform(int width, int height, float near, float far);

public:
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
    Enable(const VertexBuffer *vertexBuffer, int bindingIndex, int offset, int stride);

    void
    Disable(const VertexBuffer *vertexBuffer, int bindingIndex);

    void *
    Map(const VertexBuffer *vertexBuffer, BufferAccessMode mode);

    void
    Unmap(const VertexBuffer *vertexBuffer);

    void
    Update(const VertexBuffer *vertexBuffer);

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
    Map(const IndexBuffer *indexBuffer, BufferAccessMode mode);

    void
    Unmap(const IndexBuffer *indexBuffer);

    void
    Update(const IndexBuffer *indexBuffer);

    /************************************************************************/
    /* Texture Management                                                   */
    /************************************************************************/
    // @summary Provide a uniform interface for all texture.
    void
    Enable(int textureUnit, const Texture *texture);

    // @summary Provide a uniform interface for all texture.
    void
    Disable(int textureUnit, const Texture *texture);

    void
    Bind(const Texture1d *texture);

    void
    Unbind(const Texture1d *texture);

    void
    Enable(int textureUnit, const Texture1d *texture);

    void
    Disable(int textureUnit, const Texture1d *texture);

    void *
    Map(const Texture1d *texture, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(const Texture1d *texture, int mipmapLevel);

    void
    Update(const Texture1d *texture, int mipmapLevel);

    void
    Bind(const Texture2d *texture);

    void
    Unbind(const Texture2d *texture);

    void
    Enable(int textureUnit, const Texture2d *texture);

    void
    Disable(int textureUnit, const Texture2d *texture);

    void *
    Map(const Texture2d *texture, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(const Texture2d *texture, int mipmapLevel);

    void
    Update(const Texture2d *texture, int mipmapLevel);

    void
    Bind(const Texture2dArray *textureArray);

    void
    Unbind(const Texture2dArray *textureArray);

    void
    Enable(int textureUnit, const Texture2dArray *textureArray);

    void
    Disable(int textureUnit, const Texture2dArray *textureArray);

    void *
    Map(const Texture2dArray *textureArray, int mipmapLevel, BufferAccessMode mode);

    void
    Unmap(const Texture2dArray *textureArray, int mipmapLevel);

    void
    Update(const Texture2dArray *textureArray, int mipmapLevel);

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
    Disable(const VisualEffectPass *pass);

    void
    Enable(const VisualEffectInstancePass *pass, const Camera *camera, const Visual *visual);

    void
    Disable(const VisualEffectInstancePass *pass);

    // @summary Update effect instance's uniform.
    void
    Update(const VisualEffectInstancePass *pass, ShaderUniform *uniform, const Camera *camera, const Visual *visual);

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/
    // @summary Draw single instance of visual.
    void
    Draw(const Camera *camera, Visual *visual);

    // @summary Draw single instance of visual.
    void
    Draw(const Camera *camera, const Visual *visual, VisualEffectInstance *effectInstance);

private:
    /************************************************************************/
    /* Platform Hash Table                                                  */
    /************************************************************************/
    PlatformIndexBufferMap    mIndexBufferTable;
    PlatformVertexBufferMap   mVertexBufferTable;
    PlatformVertexFormatMap   mVertexFormatTable;
    PlatformTexture2dMap      mTexture2dTable;
    PlatformTexture2dArrayMap mTexture2dArrayTable;
    PlatformTextureSamplerMap mSamplerTable;

    PlatformShaderMap         mShaderTable;

    /************************************************************************/
    /* Renderer State                                                       */
    /************************************************************************/
    BlendState             *mBlendStateDefault;
    CullState              *mCullStateDefault;
    DepthTestState         *mDepthTestStateDefault;
    OffsetState            *mOffsetStateDefault;
    StencilTestState       *mStencilTestStateDefault;
    WireframeState         *mWireframeStateDefault;

    const BlendState       *mBlendStateCurrent;
    const CullState        *mCullStateCurrent;
    const DepthTestState   *mDepthTestStateCurrent;
    const OffsetState      *mOffsetStateCurrent;
    const StencilTestState *mStencilTestStateCurrent;
    const WireframeState   *mWireframeStateCurrent;

    Viewport                mViewport;
    Window                  mWindow;
    bool                    mWindowInitialized = false;
private:
    /************************************************************************/
    /* Platform Dependent Members                                           */
    /************************************************************************/

    /************************************************************************/
    /* Initialization and Destroy                                           */
    /************************************************************************/
    void
    InitializePlatform(const GameEngineData *data);

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
    DrawPrimitivePlatform(const Primitive *primitive, size_t primitiveInstancingNum);

private:
    PlatformRendererData *mData;
    bool                  mDataInitialized = false;
};
#pragma warning(default: 4251)

}
