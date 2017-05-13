#pragma once

#include <FalconEngine/Content/Header.h>

#include <map>

namespace FalconEngine
{

class BitmapFont;
using BitmapFontSharedPtr = std::shared_ptr<BitmapFont>;

class Model;
using ModelSharedPtr = std::shared_ptr<Model>;

class Texture2d;
using Texture2dSharedPtr = std::shared_ptr<Texture2d>;

class ShaderSource;
using ShaderSourceSharedPtr = std::shared_ptr<ShaderSource>;

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
    BitmapFontSharedPtr
    GetFontNamed(const std::string& fontName);

    BitmapFontSharedPtr
    GetFont(const std::string& fontFilePath);

    BitmapFontSharedPtr
    LoadFont(const std::string& fontAssetPath);

    ModelSharedPtr
    GetModel(const std::string& modelFilePath);

    ModelSharedPtr
    LoadModel(const std::string& modelFilePath);

    ShaderSourceSharedPtr
    GetShaderSource(const std::string& shaderFilePath);

    ShaderSourceSharedPtr
    LoadShaderSource(const std::string& shaderFilePath);

    Texture2dSharedPtr
    GetTexture(const std::string& textureFilePath);

    Texture2dSharedPtr
    LoadTexture(const std::string& textureAssetPath);

private:
    BitmapFontSharedPtr
    LoadFontInternal(const std::string& fontAssetPath);

    ModelSharedPtr
    LoadModelInternal(const std::string& modelFilePath);

    ShaderSourceSharedPtr
    LoadShaderSourceInternal(const std::string& shaderFilePath);

    Texture2dSharedPtr
    LoadTextureInternal(const std::string& textureAssetPath);

    std::map<std::string, BitmapFontSharedPtr>     mFontTable;                  // Index is file path.
    std::map<std::string, ModelSharedPtr>          mModelTable;                 // Index is file path.
    std::map<std::string, ShaderSourceSharedPtr>   mShaderSourceTable;          // Index is file path.
    std::map<std::string, Texture2dSharedPtr>      mTextureTable;               // Index is file path.
};
#pragma warning(default: 4251)

}
