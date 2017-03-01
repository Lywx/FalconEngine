#pragma once

#include <FalconEngine/ContentInclude.h>

#if FALCON_ENGINE_OS_WINDOWS

#include <map>
#include <string>
#include <vector>

namespace FalconEngine
{

class BitmapFont;
using BitmapFontSharedPtr = std::shared_ptr<BitmapFont>;

class Texture2d;
using Texture2dSharedPtr = std::shared_ptr<Texture2d>;

class AssetProcessor
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static void
    BakeFont(const std::string& fntFilePath);

    static void
    BakeModel(const std::string& modelFilePath);

    static void
    BakeTexture(const std::string& textureFilePath);

private:
    static void
    BakeFont(BitmapFont *fontPtr, const std::string& fontOutputPath);

    // @summary Load font without optimization.
    static BitmapFontSharedPtr
    LoadRawFont(const std::string& fntFilePath);

    static void
    BakeTexture(Texture2d *texturePtr, const std::string& textureOutputPath);

    static Texture2dSharedPtr
    LoadRawTexture(const std::string& textureFilePath);
};
}

#endif
