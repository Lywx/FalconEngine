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

ShaderSource *
AssetManager::GetShaderSource(std::string shaderFilePath)
{
    auto iter = mShaderSourceTable.find(shaderFilePath);
    if (iter != mShaderSourceTable.end())
    {
        return iter->second.get();
    }

    return nullptr;
}

ShaderSource *
AssetManager::LoadShaderSource(std::string shaderFilePath)
{
    auto shaderSource = GetShaderSource(shaderFilePath);
    if (shaderSource)
    {
        return shaderSource;
    }

    auto shaderSourceHandle = LoadShaderSourceInternal(shaderFilePath);
    shaderSource = shaderSourceHandle.get();
    mShaderSourceTable[shaderSource->mFilePath] = move(shaderSourceHandle);

    return shaderSource;
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
        auto font = std::make_unique<BitmapFont>("None", "None");
        {
            ifstream fontAssetStream(fontAssetPath);
            archive::binary_iarchive fontAssetArchive(fontAssetStream);
            fontAssetArchive >> *font;
        }

        // Load font texture array.
        auto fontAssetDirPath = GetFileDirectory(fontAssetPath);
        {
            // Load the first texture, then, use the texture metadata to create texture array.
            Texture2dArraySharedPtr fontPageTextureArray;
            {
                auto fontPage0TextureAssetName = font->mTextureArchiveNameVector[0];
                auto fontPage0TextureAssetPath = fontAssetDirPath + fontPage0TextureAssetName;
                auto fontPage0Texture = LoadTexture2d(fontPage0TextureAssetPath);

                // TODO(Wuxiang): Add mipmap support.
                fontPageTextureArray = std::make_shared<Texture2dArray>("None", "None", fontPage0Texture->mDimension[0],
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
            font->SetTexture(fontPageTextureArray);
        }

        // Set font texture sampler.
        auto sampler = std::make_shared<Sampler>();
        sampler->mMagnificationFilter = SamplerMagnificationFilter::Linear;
        sampler->mMinificationFilter = SamplerMinificationFilter::Linear;
        font->SetSampler(sampler);

        return font;
    }

    ThrowRuntimeException("File not found.");
}

ModelUniquePtr
AssetManager::LoadModelInternal(std::string modelFilePath)
{
    // NOTE(Wuxiang 2017-01-27 22:08): Model would not load from asset file. The
    // asset process would only preprocess model's texture in a way that is
    // beneficial for model texture loading.
    auto model = make_unique<Model>(GetFileStem(modelFilePath), modelFilePath);
    model->mFileType = AssetSource::Normal;
    AssetImporter::ImportModel(model.get(), modelFilePath);

    return model;
}

ShaderSourceUniquePtr
AssetManager::LoadShaderSourceInternal(std::string shaderFilePath)
{
    ifstream shaderStream;
    shaderStream.open(shaderFilePath.c_str(), ios_base::in);

    if (shaderStream)
    {
        string shaderLine, shaderBuffer;
        while (getline(shaderStream, shaderLine))
        {
            shaderBuffer.append(shaderLine);
            shaderBuffer.append("\r\n");
        }

        auto shaderSource = make_unique<ShaderSource>(GetFileName(shaderFilePath), shaderFilePath);
        shaderSource->mSource = move(shaderBuffer);

        return shaderSource;
    }

    return nullptr;
}

Texture2dUniquePtr
AssetManager::LoadTexture2dInternal(std::string textureAssetPath)
{
    using namespace boost;

    ifstream textureAssetStream(textureAssetPath);
    archive::binary_iarchive textureAssetArchive(textureAssetStream);

    auto texture = make_unique<Texture2d>("None", "None", 0, 0, TextureFormat::None);
    textureAssetArchive >> *texture;
    if (texture->mData == nullptr)
    {
        ThrowRuntimeException("Failed to load texture asset.");
    }

    texture->mFileType = AssetSource::Stream;
    return texture;
}

}
