#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

class Texture2d;
using Texture2dSharedPtr = std::shared_ptr<Texture2d>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API Texture2dArray : public Texture
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2dArray(const std::string& fileName, const std::string& filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage = BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture2dArray();

public:
    const Texture2d *
    GetTextureSlice(int index) const;

    void
    PushTextureSlice(Texture2dSharedPtr texture);

protected:
    // NOTE(Wuxiang): The Texture2D should not be released before owner of them
    // being released.
    std::vector<Texture2dSharedPtr> mTexture2dList;
};
#pragma warning(default: 4251)

}
