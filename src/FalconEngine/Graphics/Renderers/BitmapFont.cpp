#include <FalconEngine/Graphics/Renderers/BitmapFont.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(BitmapFont, Asset);

/************************************************************************/
/* Static Members                                                       */
/************************************************************************/
const double BitmapFont::mSizeScale = 1.32;

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
BitmapFont::BitmapFont(std::string fileName, std::string filePath) :
    Asset(fileName, filePath),
    mTextureWidth(0),
    mTextureHeight(0),
    mTexturePages(0)
{
}

BitmapFont::~BitmapFont()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
BitmapFont::SetSize(double size)
{
    mSizePt = size / mSizeScale;
    mSizePx = mSizePt / 72 * 96;
}

void
BitmapFont::SetSampler(SamplerSharedPtr sampler)
{
    mSampler = sampler;
}

const Sampler *
BitmapFont::GetSampler() const
{
    return mSampler.get();
}

void
BitmapFont::SetTexture(Texture2dArraySharedPtr texture)
{
    mTexture = texture;
}

const Texture2dArray *
BitmapFont::GetTexture() const
{
    return mTexture.get();
}

}
