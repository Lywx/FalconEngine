#pragma once

#include <FalconEngine/Core/Object.h>

namespace FalconEngine
{

enum class TextureType
{
    Texture1d,
    Texture2d,
    Texture3d,
    TextureCube,

    Count
};

class Texture : public Object
{
    FALCON_ENGINE_DECLARE_RTTI;

public:
    Texture();
    ~Texture();

};

}
