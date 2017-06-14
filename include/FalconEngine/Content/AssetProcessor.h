#pragma once

#include <FalconEngine/Content/Header.h>

#include <map>
#include <string>
#include <vector>

#include <boost/archive/binary_oarchive.hpp>

namespace FalconEngine
{
class Font;

class Texture;
class Texture1d;
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
    BakeTexture1d(const std::string& textureFilePath);

    static void
    BakeTexture2d(const std::string& textureFilePath);

private:
    static void
    BakeFont(Font *font, const std::string& fontOutputPath);

    // @summary Load font without optimization.
    static std::shared_ptr<Font>
    LoadRawFont(const std::string& fntFilePath);

    template <typename T>
    static void
    BakeTexture(T *texture, const std::string& textureOutputPath)
    {
        static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

        using namespace boost;

        // http://stackoverflow.com/questions/24313359/data-dependent-failure-when-serializing-stdvector-to-boost-binary-archive
        std::ofstream textureAssetStream(textureOutputPath, std::ios::binary);
        archive::binary_oarchive textureAssetArchive(textureAssetStream);
        textureAssetArchive << *texture;
    }

    static std::shared_ptr<Texture1d>
    LoadRawTexture1d(const std::string& textureFilePath);

    static std::shared_ptr<Texture2d>
    LoadRawTexture2d(const std::string& textureFilePath);
};
}
