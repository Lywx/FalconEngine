#include <FalconEngine/Graphics/Renderer/Resource/TextureArray.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TextureArray::TextureArray(AssetSource assetSource,
                           const std::string& fileName,
                           const std::string& filePath,
                           int width,
                           int height,
                           int depth,
                           TextureFormat format,
                           TextureType type,
                           ResourceCreationAccessMode accessMode,
                           ResourceCreationAccessUsage accessUsage,
                           int mipmapLevel) :
    Texture(assetSource, fileName, filePath,
            // https://www.khronos.org/opengl/wiki/Array_Texture
            // An array texture is a Texture where each mipmap level contains an array of images of the same size.
            width, height, depth, format, type,
            accessMode, accessUsage, ResourceStorageMode::Device, mipmapLevel)
{
}

TextureArray::~TextureArray()
{
}

}
