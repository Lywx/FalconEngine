#include <FalconEngine/Content/AssetManager.h>

#include <fstream>
#include <stdexcept>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/filesystem.hpp>

#include <FalconEngine/Content/AssetImporter.h>
#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Graphics/Renderer/Font/BitmapFont.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderSource.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>

using namespace std;

namespace FalconEngine
{

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
BitmapFontSharedPtr
AssetManager::GetFontNamed(const std::string& fontName)
{
    for (const auto &fontNameFontPair : mFontTable)
    {
        if (GetFileStem(fontNameFontPair.first) == fontName)
        {
            return GetFont(fontNameFontPair.first);
        }
    }

    return nullptr;
}

BitmapFontSharedPtr
AssetManager::GetFont(const std::string& fontFilePath)
{
    auto iter = mFontTable.find(fontFilePath);
    if (iter != mFontTable.end())
    {
        return iter->second;
    }

    return nullptr;
}

BitmapFontSharedPtr
AssetManager::LoadFont(const std::string& fontAssetPath)
{
    auto font = GetFont(RemoveFileExtension(fontAssetPath));
    if (font)
    {
        return font;
    }

    font = LoadFontInternal(fontAssetPath);
    mFontTable[font->mFilePath] = font;
    return font;
}

ModelSharedPtr
AssetManager::GetModel(const std::string& modelFilePath)
{
    auto iter = mModelTable.find(modelFilePath);
    if (iter != mModelTable.end())
    {
        return iter->second;
    }

    return nullptr;
}

ModelSharedPtr
AssetManager::LoadModel(const std::string& modelFilePath)
{
    auto model = GetModel(modelFilePath);
    if (model)
    {
        return model;
    }

    model = LoadModelInternal(modelFilePath);
    mModelTable[model->mFilePath] = model;
    return model;
}

ShaderSourceSharedPtr
AssetManager::GetShaderSource(const std::string& shaderFilePath)
{
    auto iter = mShaderSourceTable.find(shaderFilePath);
    if (iter != mShaderSourceTable.end())
    {
        return iter->second;
    }

    return nullptr;
}

ShaderSourceSharedPtr
AssetManager::LoadShaderSource(const std::string& shaderFilePath)
{
    auto shaderSource = GetShaderSource(shaderFilePath);
    if (shaderSource)
    {
        return shaderSource;
    }

    shaderSource = LoadShaderSourceInternal(shaderFilePath);
    mShaderSourceTable[shaderSource->mFilePath] = shaderSource;
    return shaderSource;
}

Texture2dSharedPtr
AssetManager::GetTexture(const std::string& textureFilePath)
{
    auto iter = mTextureTable.find(textureFilePath);
    if (iter != mTextureTable.end())
    {
        return iter->second;
    }

    return nullptr;
}

Texture2dSharedPtr
AssetManager::LoadTexture(const std::string& textureAssetPath)
{
    auto texture = GetTexture(RemoveFileExtension(textureAssetPath));
    if (texture)
    {
        return texture;
    }

    texture = LoadTextureInternal(textureAssetPath);
    mTextureTable[texture->mFilePath] = texture;

    return texture;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
BitmapFontSharedPtr
AssetManager::LoadFontInternal(const std::string& fontAssetPath)
{
    using namespace boost;

    if (Exist(fontAssetPath))
    {
        // Load font.
        auto font = std::make_shared<BitmapFont>("None", "None");
        font->mFileType = AssetSource::Stream;
        {
            // http://stackoverflow.com/questions/24313359/data-dependent-failure-when-serializing-stdvector-to-boost-binary-archive
            ifstream fontAssetStream(fontAssetPath, std::ios::binary);
            archive::binary_iarchive fontAssetArchive(fontAssetStream);
            fontAssetArchive >> *font;
        }

        // Load font texture array.
        auto fontAssetDirPath = GetFileDirectory(fontAssetPath);
        {
            // Load the first texture, then, use the texture metadata to create texture array.
            Texture2dArraySharedPtr fontPageTextureArray;
            {
                auto fontPage0TextureAssetName = font->mTextureArchiveNameList[0];
                auto fontPage0TextureAssetPath = fontAssetDirPath + fontPage0TextureAssetName;
                auto fontPage0Texture = LoadTexture(fontPage0TextureAssetPath);

                // TODO(Wuxiang): Add mipmap support.
                fontPageTextureArray = std::make_shared<Texture2dArray>("None", "None", fontPage0Texture->mDimension[0],
                                       fontPage0Texture->mDimension[1], font->mTexturePages,
                                       TextureFormat::R8G8B8A8, BufferUsage::Static, 0);
            }

            // Load the other textures.
            for (int fontPageId = 0; fontPageId < font->mTexturePages; ++fontPageId)
            {
                auto textureAssetName = font->mTextureArchiveNameList[fontPageId];
                auto textureAssetPath = fontAssetDirPath + textureAssetName;

                auto fontPageTexture = LoadTexture(textureAssetPath);
                fontPageTextureArray->PushTextureSlice(fontPageTexture);
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

    FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("File not found.");
}

ModelSharedPtr
AssetManager::LoadModelInternal(const std::string& modelFilePath)
{
    // NOTE(Wuxiang 2017-01-27 22:08): Model would not load from asset file. The
    // asset process would only preprocess model's texture in a way that is
    // beneficial for model texture loading.
    auto model = make_shared<Model>(GetFileStem(modelFilePath), modelFilePath);
    model->mFileType = AssetSource::Normal;
    AssetImporter::Import(model.get(), modelFilePath);
    return model;
}

ShaderSourceSharedPtr
AssetManager::LoadShaderSourceInternal(const std::string& shaderFilePath)
{
    if (Exist(shaderFilePath))
    {
        ifstream shaderStream(shaderFilePath.c_str(), ios_base::in);
        if (shaderStream.good())
        {
            string shaderLine, shaderBuffer;
            while (getline(shaderStream, shaderLine))
            {
                shaderBuffer.append(shaderLine);
                shaderBuffer.append("\r\n");
            }

            auto shaderSource = make_shared<ShaderSource>(GetFileName(shaderFilePath), shaderFilePath);
            shaderSource->mSource = move(shaderBuffer);

            return shaderSource;
        }

        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Failed to load the file.");
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Failed to find the file.");
    }
}

Texture2dSharedPtr
AssetManager::LoadTextureInternal(const std::string& textureAssetPath)
{
    using namespace boost;

    if (Exist(textureAssetPath))
    {
        // http://stackoverflow.com/questions/24313359/data-dependent-failure-when-serializing-stdvector-to-boost-binary-archive
        ifstream textureAssetStream(textureAssetPath, ios::binary);
        archive::binary_iarchive textureAssetArchive(textureAssetStream);

        auto texture = std::make_shared<Texture2d>("None", "None", 0, 0, TextureFormat::None);
        textureAssetArchive >> *texture;
        if (texture->mData == nullptr)
        {
            FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Failed to load texture asset.");
        }

        texture->mFileType = AssetSource::Stream;
        return texture;
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Failed to find the file.");
    }
}

}
