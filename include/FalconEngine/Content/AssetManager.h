#pragma once

#include <FalconEngine/Content/ContentInclude.h>

#include <map>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Graphics/Renderers/BitmapFont.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

namespace FalconEngine
{

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
    GetFont(std::string fontName);

    BitmapFont *
    LoadFont(std::string fontAssetPath);

    Model *
    GetModel(std::string modelName);

    Model *
    LoadModel(std::string modelFilePath);

    Texture2d *
    GetTexture2d(std::string textureName);

    Texture2d *
    LoadTexture2d(std::string textureAssetPath);

private:
    BitmapFontUniquePtr
    LoadFontInternal(std::string fontAssetPath);

    ModelUniquePtr
    LoadModelInternal(std::string modelFilePath);

    Texture2dUniquePtr
    LoadTexture2dInternal(std::string textureAssetPath);

    std::map<std::string, BitmapFontUniquePtr>     mFontTable;
    std::map<std::string, ModelUniquePtr>          mModelTable;
    std::map<std::string, Texture2dUniquePtr>      mTexture2dTable;
    std::map<std::string, Texture2dArrayUniquePtr> mTexture2dArrayTable;
};
}
