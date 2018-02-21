#include <FalconEngine/Graphics/Renderer/Resource/TextureBinding.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TextureBinding::TextureBinding():
    mTexture(nullptr)
{
}

TextureBinding::TextureBinding(const Texture *texture, TextureMode textureMode, unsigned shaderMask):
    mTexture(texture)
{
    mTextureShaderMaskList[int(textureMode)] = shaderMask;
}

}
