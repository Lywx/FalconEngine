#pragma once

#include <FalconEngine/Graphics/Header.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

// @summary Texture that actually has data storage.
class FALCON_ENGINE_API TextureBuffer : public Texture
{
public:
    TextureBuffer();
    TextureBuffer(AssetSource        assetSource,
                  const std::string& fileName,
                  const std::string& filePath,
                  int                width,
                  int                height,
                  int                depth,
                  TextureFormat      format,
                  TextureType        type,
                  BufferUsage        usage,
                  int                mipmapLevel);
    virtual ~TextureBuffer();

public:
    unsigned char *mData;
    size_t         mDataByteNum;

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive & ar)
    {
        ar & cereal::base_class<Texture>(this);

        ar & mDataByteNum;
    }
};

}
