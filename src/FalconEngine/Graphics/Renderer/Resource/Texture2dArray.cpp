#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2dArray::Texture2dArray(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage, int mipmapLevel) :
    Texture(fileName, filePath, width, height, depth, format, TextureType::Texture2dArray, usage, mipmapLevel)
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
    return mTexture2dList.at(index).get();
}

void
Texture2dArray::PushTextureSlice(Texture2dSharedPtr texture)
{
    mTexture2dList.push_back(texture);
}

}
