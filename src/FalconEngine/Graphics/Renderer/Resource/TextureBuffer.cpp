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
    if (width < 1 || height < 1 || depth < 1)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Invalid texture dimension.");
    }

    mDataByteNum = size_t(mDimension[0]) * size_t(mDimension[1]) * size_t(mDimension[2]) * TexelSize[int(mFormat)];
    mData = new unsigned char[mDataByteNum];
}

TextureBuffer::~TextureBuffer()
{
    delete[] mData;
}

}
