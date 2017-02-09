#include <FalconEngine/Content/AssetManager.h>

#include <fstream>
#include <stdexcept>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/filesystem.hpp>

#include <FalconEngine/Content/Path.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(AssetManager, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/

BitmapFont *
AssetManager::GetFont(std::string fontName)
{
    auto iter = mFontTable.find(fontName);
    if (iter != mFontTable.end())
    {
        return iter->second.get();
    }

    return nullptr;
}

BitmapFont *
AssetManager::LoadFont(std::string fontAssetPath)
{
    BitmapFont *font = GetFont(GetFileStem(fontAssetPath));
    if (font)
    {
        return font;
    }

    auto fontHandle = LoadFontInternal(fontAssetPath);
    font = fontHandle.get();
    mFontTable[font->mFileName] = move(fontHandle);
    return font;
}

Model *
AssetManager::GetModel(std::string modelName)
{
    auto iter = mModelTable.find(modelName);
    if (iter != mModelTable.end())
    {
        return iter->second.get();
    }

    return nullptr;
}

Model *
AssetManager::LoadModel(std::string modelFilePath)
{
    Model *model = GetModel(GetFileStem(modelFilePath));
    if (model)
    {
        return model;
    }

    auto modelHandle = LoadModelInternal(modelFilePath);
    model = modelHandle.get();
    mModelTable[model->mFileName] = move(modelHandle);
    return model;
}

Texture2d *
AssetManager::GetTexture(std::string textureName)
{
    auto iter = mTextureTable.find(textureName);
    if (iter != mTextureTable.end())
    {
        return iter->second.get();
    }

    return nullptr;
}

Texture2d *
AssetManager::LoadTexture(std::string textureAssetPath)
{
    Texture2d *texture = GetTexture(GetFileStem(textureAssetPath));
    if (texture)
    {
        return texture;
    }

    auto textureHandle = LoadTextureInternal(textureAssetPath);
    texture = textureHandle.get();
    mTextureTable[texture->mFileName] = move(textureHandle);

    return texture;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
BitmapFontUniquePtr
AssetManager::LoadFontInternal(std::string fontAssetPath)
{
    using namespace boost;

    if (Exist(fontAssetPath))
    {
        // Load font
        auto font = new BitmapFont("", "");
        {
            ifstream fontAssetStream(fontAssetPath);
            archive::binary_iarchive fontAssetArchive(fontAssetStream);
            fontAssetArchive >> *font;
        }

        // Load font texture
        auto fontAssetDirPath = GetFileDirectory(fontAssetPath);
        for (int fontPageId = 0; fontPageId < font->mTexturePages; ++fontPageId)
        {
            auto textureAssetName = font->mTextureArchiveNameVector[fontPageId];
            auto textureAssetPath = fontAssetDirPath + textureAssetName;
            LoadTexture(textureAssetPath);
        }

        // TODO(Wuxiang 2016-12-30 19:26): How to use font?
        //GLuint texture;
        //glGenTextures(1, &texture);
        //glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
        //glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, font.mTextureWidth, font.mTextureHeight, font.mTexturePages);
        //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //for (int fontPageId = 0; fontPageId < font.mTexturePages; ++fontPageId)
        //{
        //    string textureAssetFilePath = font.mTextureFileNameVector[fontPageId];

        //    auto textureFileName = fntDirPathString + font->mTextureFileNameVector[fontPageId];
        //    LoadTextureFile(textureFileName, font, fontPageId);

        //    Texture2d fontTexture;
        //    ifstream textureAssetStream(textureAssetFilePath);
        //    archive::binary_iarchive textureAssetArchive(textureAssetFilePath);
        //    textureAssetArchive >> fontTexture;

        //    fontTexture.mTexture = textureData;
        //    fontTexture.mTextureWidth = textureWidth;
        //    fontTexture.mTextureHeight = textureHeight;

        //    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, fontPageId, textureWidth, textureHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        //}

        return unique_ptr<BitmapFont>(font);
    }

    throw runtime_error("File not found.");
}

ModelUniquePtr
AssetManager::LoadModelInternal(std::string modelFilePath)
{
    // NOTE(Wuxiang 2017-01-27 22:08): Model would not load from asset file. The
    // asset process would only preprocess model's texture in a way that is
    // beneficial for model texture loading.
    auto model = new Model(GetFileStem(modelFilePath), modelFilePath);
    model->mFileType = AssetSource::Normal;

    // Load model using Assimp
    static Assimp::Importer modelImporter;
    const aiScene *scene = modelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        throw runtime_error(string("Error: ") + modelImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary children nodes and textures.
    model->mRootNode = Node(model, scene, scene->mRootNode);

    return unique_ptr<Model>(model);
}

Texture2dUniquePtr
AssetManager::LoadTextureInternal(std::string textureAssetPath)
{
    using namespace boost;

    ifstream textureAssetStream(textureAssetPath);
    archive::binary_iarchive textureAssetArchive(textureAssetStream);

    auto texture = new Texture2d("", "", TextureFormat::None);
    textureAssetArchive >> *texture;
    if (texture->mData == nullptr)
    {
        throw runtime_error("Failed to load texture asset.");
    }

    texture->mFileType = AssetSource::Stream;
    return unique_ptr<Texture2d>(texture);
}

}
