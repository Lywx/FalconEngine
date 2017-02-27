#pragma once

#include <FalconEngine/Content/ContentInclude.h>

#include <map>

#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderSource.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

namespace FalconEngine
{

class BitmapFont;
class Model;
class TextureArray;
class Texture2d;

class AssetManager : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

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
    BitmapFont *
    GetFontNamed(const std::string& fontName);

    BitmapFont *
    GetFont(const std::string& fontFilePath);

    BitmapFont *
    LoadFont(const std::string& fontAssetPath);

    Model *
    GetModel(const std::string& modelFilePath);

    Model *
    LoadModel(const std::string& modelFilePath);

    ShaderSource *
    GetShaderSource(const std::string& shaderFilePath);

    ShaderSource *
    LoadShaderSource(const std::string& shaderFilePath);

    Texture2d *
    GetTexture(const std::string& textureFilePath);

    Texture2d *
    LoadTexture(const std::string& textureAssetPath);

private:
    BitmapFontUniquePtr
    LoadFontInternal(const std::string& fontAssetPath);

    ModelUniquePtr
    LoadModelInternal(const std::string& modelFilePath);

    ShaderSourceUniquePtr
    LoadShaderSourceInternal(const std::string& shaderFilePath);

    Texture2dUniquePtr
    LoadTextureInternal(const std::string& textureAssetPath);

    std::map<std::string, BitmapFontUniquePtr>     mFontTable;                  // Index is file path.
    std::map<std::string, ModelUniquePtr>          mModelTable;                 // Index is file path.
    std::map<std::string, ShaderSourceUniquePtr>   mShaderSourceTable;          // Index is file path.
    std::map<std::string, Texture2dUniquePtr>      mTextureTable;             // Index is file path.
};
}
