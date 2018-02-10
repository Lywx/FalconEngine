#include <FalconEngine/Graphics/Renderer/Resource/TextureAttachment.h>

namespace FalconEngine
{
/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
TextureAttachment::TextureAttachment():
    mTexture(nullptr)
{
}

TextureAttachment::TextureAttachment(const Texture *texture, TextureMode textureMode, unsigned shaderMask):
    mTexture(texture)
{
    mTextureShaderMaskList[int(textureMode)] = shaderMask;
}

}
