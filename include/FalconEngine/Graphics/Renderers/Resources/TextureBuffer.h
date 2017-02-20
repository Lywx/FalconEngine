#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

namespace FalconEngine
{

class TextureBuffer : public Texture
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    TextureBuffer(std::string fileName, std::string filePath, int width, int height, int depth, TextureFormat format, TextureType type, BufferUsage usage, int mipmapLevel);
    virtual ~TextureBuffer();

public:
    unsigned char *mData;
    int            mDataByteNum;
};

}
