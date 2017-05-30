#pragma once

#include <FalconEngine/Content/Header.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API TextureImportOption
{
public:
    TextureImportOption() = default;

public:
    BufferUsage mTextureUsage = BufferUsage::Static;
};

}