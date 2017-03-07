#include <FalconEngine/Graphics/Renderer/Resource/TextureBuffer.h>

namespace FalconEngine
{

TextureBuffer::TextureBuffer(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel) :
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
