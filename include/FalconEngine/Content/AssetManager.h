#pragma once

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Exception.h>

#include <map>

#include <boost/filesystem.hpp>

#include <cereal/archives/portable_binary.hpp>

#include <FalconEngine/Content/ModelImportOption.h>
#include <FalconEngine/Content/TextureImportOption.h>
#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>

namespace FalconEngine
{
class TextureImportOption;

class AssetImporter;

class Font;
class Model;
class Texture;
class Texture1d;
class Texture2d;
class ShaderSource;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API AssetManager
{
public:
    static AssetManager *
    GetInstance()
    {
        // NOTE(Wuxiang): On concern about static method copy in different translation unit, read:
        // http://stackoverflow.com/questions/5372091/are-static-member-functions-in-c-copied-in-multiple-translation-units
        // http://stackoverflow.com/questions/12248747/singleton-with-multithreads
        static AssetManager sInstance;
        return &sInstance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    AssetManager();

public:
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    std::shared_ptr<Font>
    GetFontNamed(const std::string& fontName);

    std::shared_ptr<Font>
    GetFont(const std::string& fontFilePath);

    std::shared_ptr<Font>
    LoadFont(const std::string& fontAssetPath);

    std::shared_ptr<Model>
    GetModel(const std::string& modelFilePath);

    std::shared_ptr<Model>
    LoadModel(
        const std::string&       modelFilePath,
        const ModelImportOption& modelImportOption = ModelImportOption::GetDefault());

    std::shared_ptr<ShaderSource>
    GetShaderSource(const std::string& shaderFilePath);

    std::shared_ptr<ShaderSource>
    LoadShaderSource(const std::string& shaderFilePath);

    template <typename T>
    std::shared_ptr<T>
    GetTexture(const std::string& textureFilePath)
    {
        static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

        auto iter = mTextureTable.find(textureFilePath);
        if (iter != mTextureTable.end())
        {
            auto texture = iter->second;
            if (texture->mType == GetTextureType<T>())
            {
                return std::dynamic_pointer_cast<T>(iter->second);
            }
            else
            {
                FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(
                    std::string("Texture found but it had different texture type: \'")
                    + textureFilePath + "\'.");
            }
        }

        return nullptr;
    }

    template <typename T>
    std::shared_ptr<T>
    LoadTexture(
        const std::string&         textureAssetPath,
        const TextureImportOption& textureImportOption = TextureImportOption::GetDefault())
    {
        static_assert(std::is_base_of<Texture, T>::value, "Invalid texture type parameter.");

        std::shared_ptr<T> texture = GetTexture<T>(RemoveFileExtension(textureAssetPath));
        if (texture)
        {
            return texture;
        }

        std::shared_ptr<Texture> t = LoadTextureInternal(textureAssetPath, textureImportOption, GetTextureType<T>());
        texture = std::dynamic_pointer_cast<T>(t);
        mTextureTable[texture->mFilePath] = texture;
        return texture;
    }

private:
    void
    CheckFileExists(const std::string& assetPath);

    std::shared_ptr<Font>
    LoadFontInternal(const std::string& fontAssetPath);

    std::shared_ptr<Model>
    LoadModelInternal(const std::string& modelFilePath, const ModelImportOption& modelImportOption);

    std::shared_ptr<ShaderSource>
    LoadShaderSourceInternal(const std::string& shaderFilePath);

    std::shared_ptr<Texture>
    LoadTextureInternal(const std::string& textureAssetPath, const TextureImportOption& textureImportOption, TextureType textureType)
    {
        if (Exist(textureAssetPath))
        {
            std::ifstream textureAssetStream(textureAssetPath, std::ios::binary);
            cereal::PortableBinaryInputArchive textureAssetArchive(textureAssetStream);

            switch (textureType)
            {
            case TextureType::None:
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
            break;

            case TextureType::Texture1d:
            {
                return LoadTexture1dInternal(textureImportOption, textureAssetArchive);
            }
            break;

            case TextureType::Texture2d:
            {
                return LoadTexture2dInternal(textureImportOption, textureAssetArchive);
            }
            break;

            case TextureType::Texture2dArray:
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
            break;

            case TextureType::Texture3d:
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
            break;

            case TextureType::TextureCube:
            {
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
            break;

            default:
                FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
            }
        }
        else
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Failed to find the file.");
        }
    }

    std::shared_ptr<Texture1d>
    LoadTexture1dInternal(const TextureImportOption& textureImportOption, cereal::PortableBinaryInputArchive& textureAssetArchive) const;

    std::shared_ptr<Texture2d>
    LoadTexture2dInternal(const TextureImportOption& textureImportOption, cereal::PortableBinaryInputArchive& textureAssetArchive) const;

private:
    AssetImporter                                       *mImporter;

    std::map<std::string, std::shared_ptr<Font>>         mFontTable;            // Index is file path.
    std::map<std::string, std::shared_ptr<Model>>        mModelTable;           // Index is file path.
    std::map<std::string, std::shared_ptr<ShaderSource>> mShaderSourceTable;    // Index is file path.
    std::map<std::string, std::shared_ptr<Texture>>      mTextureTable;         // Index is file path.
};
#pragma warning(default: 4251)

}
