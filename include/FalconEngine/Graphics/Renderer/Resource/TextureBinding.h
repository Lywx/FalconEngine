#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>

namespace FalconEngine
{

using TextureShaderMaskList = std::array<unsigned int, int(TextureMode::Count)>;

FALCON_ENGINE_CLASS_BEGIN TextureBinding final
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    TextureBinding();
    TextureBinding(const Texture * texture, TextureMode textureMode, unsigned int shaderMask);
    ~TextureBinding() = default;

public:
    const Texture *mTexture;

    // Shader mask for different texture mode. The array is indexed by texture
    // mode enum value.
    TextureShaderMaskList mTextureShaderMaskList;
};
FALCON_ENGINE_CLASS_END

}
