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
    auto font = GetFont(GetFileStem(fontAssetPath));
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
    auto model = GetModel(GetFileStem(modelFilePath));
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
AssetManager::GetTexture2d(std::string textureName)
{
    auto iter = mTexture2dTable.find(textureName);
    if (iter != mTexture2dTable.end())
    {
        return iter->second.get();
    }

    return nullptr;
}

Texture2d *
AssetManager::LoadTexture2d(std::string textureAssetPath)
{
    auto texture = GetTexture2d(GetFileStem(textureAssetPath));
    if (texture)
    {
        return texture;
    }

    auto textureHandle = LoadTexture2dInternal(textureAssetPath);
    texture = textureHandle.get();
    mTexture2dTable[texture->mFileName] = move(textureHandle);

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
        // Load font.
        auto font = new BitmapFont("None", "None");
        {
            ifstream fontAssetStream(fontAssetPath);
            archive::binary_iarchive fontAssetArchive(fontAssetStream);
            fontAssetArchive >> *font;
        }

        // Load font texture array.
        auto fontAssetDirPath = GetFileDirectory(fontAssetPath);
        {
            // Load the first texture, then, use the texture metadata to create texture array.
            Texture2dArray *fontPageTextureArray;
            {
                auto fontPage0TextureAssetName = font->mTextureArchiveNameVector[0];
                auto fontPage0TextureAssetPath = fontAssetDirPath + fontPage0TextureAssetName;
                auto fontPage0Texture = LoadTexture2d(fontPage0TextureAssetPath);

                // TODO(Wuxiang): Add mipmap support.
                fontPageTextureArray = new Texture2dArray("None", "None", fontPage0Texture->mDimension[0],
                        fontPage0Texture->mDimension[1], font->mTexturePages,
                        TextureFormat::R8G8B8A8, BufferUsage::Static, 0);
            }

            // Load the other textures.
            for (int fontPageId = 1; fontPageId < font->mTexturePages; ++fontPageId)
            {
                auto textureAssetName = font->mTextureArchiveNameVector[fontPageId];
                auto textureAssetPath = fontAssetDirPath + textureAssetName;

                auto fontPageTexture = LoadTexture2d(textureAssetPath);
                fontPageTextureArray->PushTexture2d(fontPageTexture);
            }
            font->SetTexture(Texture2dArraySharedPtr(fontPageTextureArray));
        }

        // Set font texture sampler.
        auto sampler = new Sampler();
        sampler->mMagnificationFilter = SamplerMagnificationFilter::Linear;
        sampler->mMinificationFilter = SamplerMinificationFilter::Linear;
        font->SetSampler(SamplerSharedPtr(sampler));

        return unique_ptr<BitmapFont>(font);
    }

    ThrowRuntimeException("File not found.");
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
        ThrowRuntimeException(string("Error: ") + modelImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary children nodes and textures.
    model->mRootNode = Node(model, scene, scene->mRootNode);

    return unique_ptr<Model>(model);
}

Texture2dUniquePtr
AssetManager::LoadTexture2dInternal(std::string textureAssetPath)
{
    using namespace boost;

    ifstream textureAssetStream(textureAssetPath);
    archive::binary_iarchive textureAssetArchive(textureAssetStream);

    auto texture = new Texture2d("None", "None", 0, 0, TextureFormat::None);
    textureAssetArchive >> *texture;
    if (texture->mData == nullptr)
    {
        ThrowRuntimeException("Failed to load texture asset.");
    }

    texture->mFileType = AssetSource::Stream;
    return unique_ptr<Texture2d>(texture);
}

}
