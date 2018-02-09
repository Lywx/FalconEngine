#include <FalconEngine/Platform/Direct3D/Direct3DTexture.h>

#if defined(FALCON_ENGINE_API_DIRECT3D)

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
PlatformTexture::PlatformTexture(Renderer *renderer, const Texture *texture) :
    PlatformResource(renderer, texture),
    mTexturePtr(texture)
{
    mFormat = Direct3DResourceFormat[int(texture->mFormat)];
    mUsage = Direct3DResourceAccessUsage[int(texture->mAccessMode)];
}

PlatformTexture::~PlatformTexture()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
PlatformTexture::Enable(Renderer *renderer, int textureUnit)
{
    // TODO(Wuxiang): Support multiple shader stage.
    // TODO(Wuxiang): Support other resource view.
    renderer->mData->GetContext()->PSSetShaderResources(textureUnit, 1, &mShaderResourceView);
}

void
PlatformTexture::Disable(Renderer *renderer, int textureUnit)
{
    // TODO(Wuxiang): Support multiple shader stage.
    // TODO(Wuxiang): Support other resource view.
    renderer->mData->GetContext()->PSSetShaderResources(textureUnit, 1, nullptr);
}

}

#endif