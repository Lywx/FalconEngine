#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

using TextureShaderMaskList = std::array<unsigned int, int(TextureMode::Count)>;

FALCON_ENGINE_CLASS_BEGIN TextureAttachment final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    TextureAttachment();
    TextureAttachment(const Texture * texture, TextureMode textureMode, unsigned int shaderMask);
    ~TextureAttachment() = default;

public:
    const Texture *mTexture;

    // Shader mask for different texture mode. The array is indexed by texture
    // mode enum value.
    TextureShaderMaskList mTextureShaderMaskList;
};
FALCON_ENGINE_CLASS_END

}
