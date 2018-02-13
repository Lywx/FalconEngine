#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Core/Exception.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture2d, TextureType::Texture2d);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2d::Texture2d()
{
}

Texture2d::Texture2d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
                     int height,
                     TextureFormat format,
                     ResourceCreationAccessMode accessMode,
                     ResourceCreationAccessUsage accessUsage,
                     int mipmapLevel) :
    Texture(assetSource, fileName, filePath, width, height, 1, format,
            TextureType::Texture2d, accessMode, accessUsage,
            ResourceStorageMode::Host, mipmapLevel)
{
}

Texture2d::Texture2d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
                     int height,
                     int depth,
                     TextureFormat format,
                     TextureType type,
                     ResourceCreationAccessMode accessMode,
                     ResourceCreationAccessUsage accessUsage,
                     ResourceStorageMode storageMode,
                     int mipmapLevel) :
    Texture(assetSource, fileName, filePath,

            // https://www.khronos.org/opengl/wiki/Array_Texture
            // An array texture is a Texture where each mipmap level contains an array of images of the same size.
            width, height, depth, format, type,
            accessMode, accessUsage, storageMode, mipmapLevel)
{
}

Texture2d::~Texture2d()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Texture2d *
Texture2d::GetTextureSlice(int textureIndex) const
{
    if (textureIndex != 0)
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    return this;
}

}
