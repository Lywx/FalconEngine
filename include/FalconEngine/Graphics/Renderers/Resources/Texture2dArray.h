#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <memory>
#include <vector>

#include <FalconEngine/Graphics/Renderers/Resources/Texture.h>

namespace FalconEngine
{

class Texture2d;
class Texture2dArray : public Texture
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Texture2dArray(std::string fileName, std::string filePath, int width, int height, int depth, TextureFormat format, BufferUsage usage = BufferUsage::Static, int mipmapLevel = 0);
    virtual ~Texture2dArray();

public:
    const Texture2d *
    GetTexture2d(int index) const;

    void
    PushTexture2d(const Texture2d *texture);

protected:
    std::vector<const Texture2d *> mTexture2dVector;
};

typedef std::shared_ptr<Texture2dArray> Texture2dArraySharedPtr;
typedef std::unique_ptr<Texture2dArray> Texture2dArrayUniquePtr;

}
