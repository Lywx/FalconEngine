#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture2dArray, TextureType::Texture2dArray);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2dArray::Texture2dArray(AssetSource        assetSource,
                               const std::string& fileName,
                               const std::string& filePath,
                               int                width,
                               int                height,
                               int                depth,
                               TextureFormat      format,
                               BufferUsage        usage,
                               int                mipmapLevel) :
    TextureArray(assetSource, fileName, filePath, width, height, depth, format,
                 TextureType::Texture2dArray, usage, mipmapLevel)
{
}

Texture2dArray::~Texture2dArray()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Texture2d *
Texture2dArray::GetTextureSlice(int index) const
{
    return mTextureList.at(index).get();
}

void
Texture2dArray::PushTextureSlice(std::shared_ptr<Texture2d> texture)
{
    mDimensionList.push_back(texture->mDimension);
    mTextureList.push_back(texture);
}

}
