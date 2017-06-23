#include <FalconEngine/Graphics/Renderer/Font/Font.h>

namespace FalconEngine
{

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const double Font::mSizeScale = 1.32;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Font::Font()
{
}

Font::Font(AssetSource assetSource, const std::string& fileName, const std::string& filePath) :
    Asset(assetSource, AssetType::Font, fileName, filePath)
{
}

Font::~Font()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
Font::SetSize(double size)
{
    mSizePt = size / mSizeScale;
    mSizePx = mSizePt / 72 * 96;
}

void
Font::SetSampler(std::shared_ptr<Sampler> sampler)
{
    FALCON_ENGINE_CHECK_NULLPTR(sampler);

    mSampler = sampler;
}

const Sampler *
Font::GetSampler() const
{
    return mSampler.get();
}

void
Font::SetTexture(std::shared_ptr<Texture2dArray> texture)
{
    FALCON_ENGINE_CHECK_NULLPTR(texture);

    mTexture = texture;
}

const Texture2dArray *
Font::GetTexture() const
{
    return mTexture.get();
}

}
