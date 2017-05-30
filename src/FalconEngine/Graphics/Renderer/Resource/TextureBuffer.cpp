#include <FalconEngine/Graphics/Renderer/Resource/TextureBuffer.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TextureBuffer::TextureBuffer(AssetSource        assetSource,
                             const std::string& fileName,
                             const std::string& filePath,
                             int                width,
                             int                height,
                             int                depth,
                             TextureFormat      format,
                             TextureType        type,
                             BufferUsage        usage,
                             int                mipmapLevel) :
    Texture(assetSource, fileName, filePath, width, height, depth, format, type, usage, mipmapLevel)
{
    mDataByteNum = mDimension[0] * mDimension[1] * mDimension[2] * TexelSize[int(mFormat)];

    assert(mDataByteNum >= 0);

    mData = new unsigned char[mDataByteNum];
}

TextureBuffer::~TextureBuffer()
{
    delete[] mData;
}

}
