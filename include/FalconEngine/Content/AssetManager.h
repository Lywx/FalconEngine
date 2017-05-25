#pragma once

#include <FalconEngine/Content/Header.h>

#include <map>

namespace FalconEngine
{

class AssetImporter;

class Font;
class Model;
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
    AssetManager();
    ~AssetManager();

    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

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
    LoadModel(const std::string& modelFilePath);

    std::shared_ptr<ShaderSource>
    GetShaderSource(const std::string& shaderFilePath);

    std::shared_ptr<ShaderSource>
    LoadShaderSource(const std::string& shaderFilePath);

    std::shared_ptr<Texture2d>
    GetTexture(const std::string& textureFilePath);

    std::shared_ptr<Texture2d>
    LoadTexture(const std::string& textureAssetPath);

private:
    void
    CheckFileExists(const std::string& assetPath);

    std::shared_ptr<Font>
    LoadFontInternal(const std::string& fontAssetPath);

    std::shared_ptr<Model>
    LoadModelInternal(const std::string& modelFilePath);

    std::shared_ptr<ShaderSource>
    LoadShaderSourceInternal(const std::string& shaderFilePath);

    std::shared_ptr<Texture2d>
    LoadTextureInternal(const std::string& textureAssetPath);

private:
    AssetImporter                                       *mImporter;

    std::map<std::string, std::shared_ptr<Font>>         mFontTable;            // Index is file path.
    std::map<std::string, std::shared_ptr<Model>>        mModelTable;           // Index is file path.
    std::map<std::string, std::shared_ptr<ShaderSource>> mShaderSourceTable;    // Index is file path.
    std::map<std::string, std::shared_ptr<Texture2d>>    mTextureTable;         // Index is file path.
};
#pragma warning(default: 4251)

}
