#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Core/Exception.h>

namespace FalconEngine
{

FALCON_ENGINE_TEXTURE_IMPLEMENT(Texture1d, TextureType::Texture1d);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture1d::Texture1d()
{
}

Texture1d::Texture1d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
                     TextureFormat format,
                     ResourceCreationAccessMode accessMode,
                     ResourceCreationAccessUsage accessUsage,
                     int mipmapLevel) :
    Texture(assetSource, fileName, filePath, width, 1, 1, format, TextureType::Texture1d, accessMode, accessUsage, ResourceStorageMode::Host, mipmapLevel)
{
}

Texture1d::Texture1d(AssetSource assetSource,
                     const std::string& fileName,
                     const std::string& filePath,
                     int width,
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
            width, 1, depth, format, type,
            accessMode, accessUsage, storageMode, mipmapLevel)
{
}

Texture1d::~Texture1d()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
const Texture1d *
Texture1d::GetTextureSlice(int textureIndex) const
{
    if (textureIndex != 0)
    {
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }

    return this;
}

}
