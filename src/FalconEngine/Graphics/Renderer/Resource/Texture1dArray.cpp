#include <FalconEngine/Graphics/Renderer/Resource/Texture1dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture1dArray, TextureType::Texture1dArray);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture1dArray::Texture1dArray(AssetSource assetSource,
                               const std::string& fileName,
                               const std::string& filePath,
                               int width,
                               int depth,
                               TextureFormat format,
                               ResourceCreationAccessMode accessMode,
                               ResourceCreationAccessUsage accessUsage,
                               int mipmapLevel) :
    Texture1d(assetSource, fileName, filePath,
              // An array texture is a Texture where each mipmap level contains
              // an array of images of the same size.
              width, depth, format,
              TextureType::Texture1dArray, accessMode, accessUsage,
              ResourceStorageMode::Device, mipmapLevel)
{
}

Texture1dArray::~Texture1dArray()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Texture1d *
Texture1dArray::GetTextureSlice(int index) const
{
    return mTextureList.at(index).get();
}

void
Texture1dArray::PushTextureSlice(const std::shared_ptr<Texture1d>& texture)
{
    mTextureList.push_back(texture);
}

}
