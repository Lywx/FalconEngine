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
    /* Public Members                                                       */
    /************************************************************************/
    static void
    BakeFont(std::string fntFilePath);

    static void
    BakeModel(std::string modelFilePath);

    static void
    BakeTexture2d(std::string textureFilePath);

private:
    static void
    BakeFont(BitmapFont *fontPtr, std::string fontOutputPath);

    // @summary Load font without optimization.
    static BitmapFontUniquePtr
    LoadRawFont(std::string fntFilePath);

    static void
    BakeTexture2d(Texture2d *texturePtr, std::string textureOutputPath);

    static Texture2dUniquePtr
    LoadRawTexture2d(std::string textureFilePath);
};
}

#endif
