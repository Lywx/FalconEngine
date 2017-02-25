#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Texture2dArray, Texture);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Texture2dArray::Texture2dArray(std::string fileName, std::string filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage, int mipmapLevel) :
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
    return mTexture2dVector.at(index);
}

void
Texture2dArray::PushTextureSlice(const Texture2d *texture)
{
    mTexture2dVector.push_back(texture);
}

}
