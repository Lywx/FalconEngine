#pragma once

#include <FalconEngine/Content/ContentInclude.h>

#if FALCON_ENGINE_OS_WINDOWS

#include <map>
#include <string>
#include <vector>

#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

namespace FalconEngine
{

class AssetProcessor
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    AssetProcessor();
    ~AssetProcessor();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    BakeFont(std::string fntFilePath);

    void
    BakeModel(std::string modelFilePath);

    void
    BakeTexture(std::string textureFilePath);

private:
    void
    BakeFont(BitmapFont *fontPtr, std::string fontOutputPath);

    // @summary Load font without optimization.
    BitmapFontUniquePtr
    LoadRawFont(std::string fntFilePath);

    void
    BakeTexture(Texture2d *texturePtr, std::string textureOutputPath);

    Texture2dUniquePtr
    LoadRawTexture(std::string textureFilePath);

    // @param materialPathsBaked material texture
    void
    BakeMaterial(aiMaterial               *material,
                 aiTextureType             textureType,
                 std::vector<std::string>& texturePathsBaked);
};
}

#endif
