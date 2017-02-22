#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <map>
#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Viewport.h>

namespace FalconEngine
{

/************************************************************************/
/* Renderer                                                             */
/************************************************************************/
class BitmapFontRenderer;

/************************************************************************/
/* Rendering Pipeline                                                   */
/************************************************************************/
class BitmapFont;
class BitmapText;
class Camera;
class Shader;
class Visual;
class VisualEffectInstance;
class VisualPass;

/************************************************************************/
/* Renderer Resource                                                    */
/************************************************************************/
class Buffer;
enum class BufferAccessMode;
class VertexBuffer;
class VertexFormat;
class IndexBuffer;

class Texture;
class Texture1d;
class Texture2d;
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
class Renderer
{
public:
    /************************************************************************/
    /* Platform Independent Members                                         */
    /************************************************************************/
    typedef std::map<const VertexBuffer *, PlatformVertexBuffer *> PlatformVertexBufferTable;
    typedef std::map<const VertexFormat *, PlatformVertexFormat *> PlatformVertexFormatTable;
    typedef std::map<const IndexBuffer *,  PlatformIndexBuffer *> PlatformIndexBufferTable;
    typedef std::map<const Texture1d *, PlatformTexture1d *> PlatformTexture1dTable;
    typedef std::map<const Texture2d *, PlatformTexture2d *> PlatformTexture2dTable;
    typedef std::map<const Texture2dArray *, PlatformTexture2dArray *> PlatformTexture2dArrayTable;
    typedef std::map<const Texture3d *, PlatformTexture3d *> PlatformTexture3dTable;
    typedef std::map<const Sampler *, PlatformSampler *> PlatformTextureSamplerTable;

    typedef std::map<const Shader *, PlatformShader *> PlatformShaderTable;

protected:
    void
    Initialize(int width, int height);

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
    Enable(const VisualPass *pass);

    void
    Disable(const VisualPass *pass);

    /************************************************************************/
    /* Draw                                                                 */
    /************************************************************************/

    // @summary Draw single instance of visual.
    void
    Draw(Visual *visual);

    // @summary Draw single instance of visual.
    void
    Draw(const Visual *visual, VisualEffectInstance *instance);

    void
    Draw(const VertexFormat *vertexFormat, const VertexBuffer *vertexBuffer, VisualEffectInstance *instance);

public:
    int                     mWidth;
    int                     mHeight;

    Camera                 *mCamera;
    Viewport                mViewport;

    BitmapFontRenderer     *mFontRenderer;

private:
    /************************************************************************/
    /* Platform Hash Table                                                  */
    /************************************************************************/
    PlatformIndexBufferTable        mIndexBufferTable;
    PlatformVertexBufferTable       mVertexBufferTable;
    PlatformVertexFormatTable       mVertexFormatTable;
    PlatformTexture2dTable          mTexture2dTable;
    PlatformTexture2dArrayTable     mTexture2dArrayTable;
    PlatformTextureSamplerTable     mSamplerTable;

    PlatformShaderTable             mShaderTable;

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


public:
    /************************************************************************/
    /* Platform Dependent Members                                           */
    /************************************************************************/

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Renderer(std::string caption, int width, int height);
    virtual ~Renderer();

    /************************************************************************/
    /* State Management                                                     */
    /************************************************************************/
    void
    SetBlendState(const BlendState *blendState);

    void
    SetCullState(const CullState *cullState);

    void
    SetDepthTestState(const DepthTestState *depthTestState);

    void
    SetOffsetState(const OffsetState *offsetState);

    void
    SetStencilTestState(const StencilTestState *stencilTestState);

    void
    SetWireframeState(const WireframeState *wireframeState);

    /************************************************************************/
    /* Viewport Management                                                  */
    /************************************************************************/

    // @note The viewport is specified in right-handed screen
    // coordinates. The origin is the lower-left corner of the screen, the
    // y-axis points upward, and the x-axis points rightward.
    void
    SetViewport(float x, float y, float width, float height, float near, float far);

    void
    GetViewport(float& x, float& y, float& width, float& height, float& near, float& far) const;

    void
    SetWindowSize(int width, int height);

    /************************************************************************/
    /* Default Framebuffer Management                                       */
    /************************************************************************/
    void
    ClearColorBuffer(Vector4f color);

    void
    ClearDepthBuffer(float depth);

    void
    ClearStencilBuffer(unsigned int stencil);

    void
    ClearBuffers(Vector4f color, float depth, unsigned int stencil);

    void
    SwapBuffers();

private:
    void
    InitializePlatform();

    void
    DrawPrimitive(const Visual *visual);

    PlatformRendererData *mData;
};

}
