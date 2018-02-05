#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>

namespace FalconEngine
{

class FALCON_ENGINE_API TextureImportOption
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static TextureImportOption GetDefault()
    {
        static const TextureImportOption sDefault = TextureImportOption();
        return sDefault;
    }

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    TextureImportOption() = default;

public:
    ResourceCreationAccessUsage mTextureUsage = ResourceCreationAccessUsage::Static;
};

}