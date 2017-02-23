#pragma once

#include <FalconEngine/Content/ContentInclude.h>

#include <map>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Content/AssetImporter.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Shaders/ShaderSource.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

namespace FalconEngine
{

class BitmapFont;
class Model;
class Texture2d;
class TextureArray;

class AssetManager : Object
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    static AssetManager *GetInstance()
    {
        // http://stackoverflow.com/questions/12248747/singleton-with-multithreads
        static AssetManager instance;
        return &instance;
    }

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    AssetManager();
    ~AssetManager();

    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    BitmapFont *
    GetFontNamed(std::string fontName);

    BitmapFont *
    GetFont(std::string fontFilePath);

    BitmapFont *
    LoadFont(std::string fontAssetPath);

    Model *
    GetModel(std::string modelFilePath);

    Model *
    LoadModel(std::string modelFilePath);

    ShaderSource *
    GetShaderSource(std::string shaderFilePath);

    ShaderSource *
    LoadShaderSource(std::string shaderFilePath);

    Texture2d *
    GetTexture(std::string textureFilePath);

    Texture2d *
    LoadTexture(std::string textureAssetPath);

private:
    BitmapFontUniquePtr
    LoadFontInternal(std::string fontAssetPath);

    ModelUniquePtr
    LoadModelInternal(std::string modelFilePath);

    ShaderSourceUniquePtr
    LoadShaderSourceInternal(std::string shaderFilePath);

    Texture2dUniquePtr
    LoadTextureInternal(std::string textureAssetPath);

    std::map<std::string, BitmapFontUniquePtr>     mFontTable;                  // Index is file path.
    std::map<std::string, ModelUniquePtr>          mModelTable;                 // Index is file path.
    std::map<std::string, ShaderSourceUniquePtr>   mShaderSourceTable;          // Index is file path.
    std::map<std::string, Texture2dUniquePtr>      mTextureTable;             // Index is file path.
};
}
