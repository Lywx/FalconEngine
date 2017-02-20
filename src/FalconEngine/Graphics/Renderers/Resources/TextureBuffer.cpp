#include <FalconEngine/Graphics/Renderers/Resources/TextureBuffer.h>

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(TextureBuffer, Texture);

TextureBuffer::TextureBuffer(std::string fileName, std::string filePath, int width, int height, int depth, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel) :
    Texture(fileName, filePath, width, height, depth, format, type, usage, mipmapLevel)
{
    mDataByteNum = mDimension[0] * mDimension[1] * mDimension[2] * TexelSize[int(mFormat)];
    mData = new unsigned char[mDataByteNum];
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TextureBuffer::~TextureBuffer()
{
    delete[] mData;
}

}
