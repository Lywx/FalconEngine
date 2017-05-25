#pragma once

#include <FalconEngine/Content/Header.h>

#include <map>
#include <string>
#include <vector>

namespace FalconEngine
{

class Font;

class Texture2d;

class FALCON_ENGINE_API AssetProcessor
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
    BakeFont(Font *fontPtr, const std::string& fontOutputPath);

    // @summary Load font without optimization.
    static std::shared_ptr<Font>
    LoadRawFont(const std::string& fntFilePath);

    static void
    BakeTexture(Texture2d *texturePtr, const std::string& textureOutputPath);

    static std::shared_ptr<Texture2d>
    LoadRawTexture(const std::string& textureFilePath);
};
}
