#include <FalconEngine/Content/AssetProcessor.h>

#if FALCON_ENGINE_OS_WINDOWS
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <boost/algorithm/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <stb/stb_image.h>

#include <FalconEngine/Content/Path.h>

using namespace boost;
using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AssetProcessor::BakeFont(const std::string& fntFilePath)
{
    auto fontHandle = LoadRawFont(fntFilePath);
    if (fontHandle)
    {
        auto fontOuptutPath = AddAssetExtension(fntFilePath);
        BakeFont(fontHandle.get(), fontOuptutPath);

        // Bake font's textures
        auto fntDirPath = GetFileDirectory(fntFilePath);
        for (int fontPageId = 0; fontPageId < fontHandle->mTexturePages; ++fontPageId)
        {
            auto textureFilePath = fntDirPath + fontHandle->mTextureFileNameVector[fontPageId];
            auto texture = LoadRawTexture2d(textureFilePath);
            BakeTexture2d(texture.get(), AddAssetExtension(textureFilePath));
        }
    }
}

void
AssetProcessor::BakeFont(BitmapFont *font, const std::string& fontOutputPath)
{
    // http://stackoverflow.com/questions/24313359/data-dependent-failure-when-serializing-stdvector-to-boost-binary-archive
    ofstream fontAssetStream(fontOutputPath, std::ios::binary);
    archive::binary_oarchive fontAssetArchive(fontAssetStream);
    fontAssetArchive << *font;
}

pair<string, string>
ReadFntPair(const string fntPair)
{
    static vector<string> sLineElems;
    sLineElems.clear();

    split(sLineElems, fntPair, is_any_of("="));
    return make_pair(sLineElems[0], sLineElems[1]);
}

// @summary Extract the content in line into pairs and push them into the font
// setting table.
void
PushFntMetaLine(map<string, string>& fontSettingTable, vector<string>& fontSettingElems)
{
    // Skip first element
    for (size_t i = 1; i < fontSettingElems.size(); ++i)
    {
        if (fontSettingElems[i].size() != 0)
        {
            pair<string, string> keyValuePair = ReadFntPair(fontSettingElems[i]);
            fontSettingTable[keyValuePair.first] = trim_copy_if(keyValuePair.second, is_any_of("\""));
        }
    }
}

void
LoadFntGlyphLine(
    BitmapFont&     font,
    vector<string>& fontGlyphElems,
    size_t          fontGlyphIndex,
    int             fontGlyphPT,
    int             fontGlyphPR,
    int             fontGlyphPB,
    int             fontGlyphPL)
{
    // NOTE(Wuxiang): Using preallocated map to improved performance. There is no
    // need to clear the map because all the data is overwritten by new glyph.
    static map<string, string> sFontGlyphPairTable;

    // Skip "char", the first element
    for (size_t i = 1; i < fontGlyphElems.size(); ++i)
    {
        if (fontGlyphElems[i].size() != 0)
        {
            pair<string, string> keyValuePair = ReadFntPair(fontGlyphElems[i]);
            sFontGlyphPairTable[keyValuePair.first] = keyValuePair.second;
        }
    }

    // Total horizontal padding
    int fontGlyphPWidth = fontGlyphPL + fontGlyphPR;

    // NOTE(Wuxiang): The fnt file has to configured to padding = 0 in all directions.
    int id = lexical_cast<int>(sFontGlyphPairTable.at("id").c_str());
    double width = lexical_cast<double>(sFontGlyphPairTable.at("width").c_str());
    double height = lexical_cast<double>(sFontGlyphPairTable.at("height").c_str());

    // NOTE(Wuxiang): Only amend padding data in vertex related data. Texture quad
    // should be expanded as the padding expands.
    double offsetX = lexical_cast<double>(sFontGlyphPairTable.at("xoffset").c_str()) + fontGlyphPL;
    double offsetY = lexical_cast<double>(sFontGlyphPairTable.at("yoffset").c_str()) + fontGlyphPT;
    double advance = lexical_cast<double>(sFontGlyphPairTable.at("xadvance").c_str()) - fontGlyphPWidth;

    // NOTE(Wuxiang): The fnt file x, y represents left and top pixel coordinate
    // origined from top-left corner of the png file. However, in opengl s1, t1
    // represents left and bottom coordinate origined from bottom-left corner of
    // the screen.
    double s1 = lexical_cast<double>(sFontGlyphPairTable.at("x").c_str()) / font.mTextureWidth;
    double s2 = s1 + width / font.mTextureWidth;
    double t2 = (font.mTextureHeight - lexical_cast<double>(sFontGlyphPairTable.at("y").c_str())) / font.mTextureHeight;
    double t1 = t2 - height / font.mTextureHeight;

    int page = lexical_cast<int>(sFontGlyphPairTable.at("page").c_str());

    // NOTE(Wuxiang): Indirect lookup in glyph table. First you look up the glyph
    // index with the codepoint, which indexes into the glyph table. Then you use
    // the glyph index to look up the glyph. This implementation achieve best
    // performance and lowest storage in runtime.
    font.mGlyphIndexTable[id] = fontGlyphIndex;
    font.mGlyphTable.push_back(BitmapGlyph(id, width, height, offsetX,
                                           offsetY, advance, page, s1, t1, s2, t2));
}

// @summary Load page content line into font data.
void
LoadFntPageLine(BitmapFont& font, vector<string>& fontPageElems)
{
    // NOTE(Wuxiang): Using preallocated map to improved performance. There is no
    // need to clear the map because all the data is overwritten by new page.
    static map<string, string> sFontPagePairs;

    // Skip "page", the first element
    for (size_t i = 1; i < fontPageElems.size(); ++i)
    {
        if (fontPageElems[i].size() != 0)
        {
            pair<string, string> keyValuePair = ReadFntPair(fontPageElems[i]);
            sFontPagePairs[keyValuePair.first] = keyValuePair.second;
        }
    }

    auto fontTextureFileName = trim_copy_if(sFontPagePairs.at("file"), is_any_of("\""));
    font.mTextureFileNameVector.push_back(fontTextureFileName);
    font.mTextureArchiveNameVector.push_back(AddAssetExtension(fontTextureFileName));
}

// @Return: whether should continue reading texture file. If you should, the
// pointer points to the half loaded font.
std::unique_ptr<BitmapFont>
LoadFntFile(const std::string& fntFilePath)
{
    static vector<string> sFntElems;
    static string         sFntLine;
    ifstream              fntStream(fntFilePath);

    // Try open fnt file.
    if (!fntStream.good())
    {
        FALCON_ENGINE_THROW_EXCEPTION("Failed to load fnt file.");
    }

    static map<string, string> sFontSettingTable;
    sFontSettingTable.clear();

    // Read first 2 lines of font metadata
    {
        // 1st line. Since the face name could contain space character, we need to
        // process this line separately
        {
            getline(fntStream, sFntLine);

            auto faceLhsQuote = find_nth(sFntLine, "\"", 0);
            auto faceRhsQuote = find_nth(sFntLine, "\"", 1);
            auto faceLength = distance(faceLhsQuote.begin(), faceRhsQuote.begin());
            auto faceNameIndex = distance(sFntLine.begin(), faceLhsQuote.begin()) + 1;
            auto faceSettingIndex = distance(sFntLine.begin(), faceLhsQuote.begin()) - 5;
            auto sizeSettingIndex = distance(sFntLine.begin(), faceRhsQuote.begin()) + 2;

            sFontSettingTable["face"] = sFntLine.substr(faceNameIndex, faceLength);
            sFntLine.erase(faceSettingIndex, sizeSettingIndex - faceSettingIndex);
            split(sFntElems, sFntLine, is_space());
            PushFntMetaLine(sFontSettingTable, sFntElems);
        }

        // 2nd line
        sFntElems.clear();
        getline(fntStream, sFntLine);
        split(sFntElems, sFntLine, is_space());

        PushFntMetaLine(sFontSettingTable, sFntElems);
    }

    // Create font
    auto font = new BitmapFont(GetFileStem(fntFilePath), fntFilePath);
    font->mFileType = AssetSource::Normal;

    // Read page number and read page specific filename
    font->mTexturePages = lexical_cast<int>(sFontSettingTable.at("pages"));
    for (int i = 0; i < font->mTexturePages; ++i)
    {
        sFntElems.clear();
        getline(fntStream, sFntLine);
        split(sFntElems, sFntLine, is_space());

        LoadFntPageLine(*font, sFntElems);
    }

    // Extract some necessary metadata in font-> They are useful when we load
    // glyph data.
    int fontSize;

    // Padding top
    int fontGlyphPT;

    // Padding bottom
    int fontGlyphPB;

    // Padding left
    int fontGlyphPL;

    // Padding right
    int fontGlyphPR;
    {
        fontSize = lexical_cast<int>(sFontSettingTable.at("size"));
        font->mLineBase = lexical_cast<uint32>(sFontSettingTable.at("base"));
        font->mLineHeight = lexical_cast<uint32>(sFontSettingTable.at("lineHeight"));
        font->mTextureWidth = lexical_cast<int>(sFontSettingTable.at("scaleW"));
        font->mTextureHeight = lexical_cast<int>(sFontSettingTable.at("scaleH"));

        sFntElems.clear();
        auto& glyphPaddingString = sFontSettingTable.at("padding");
        trim(glyphPaddingString);
        split(sFntElems, glyphPaddingString, is_any_of(","));

        fontGlyphPT = lexical_cast<int>(sFntElems[0]);
        fontGlyphPR = lexical_cast<int>(sFntElems[1]);
        fontGlyphPB = lexical_cast<int>(sFntElems[2]);
        fontGlyphPL = lexical_cast<int>(sFntElems[3]);
    }

    // Read character glyphs
    {
        // Read glyph number
        sFntElems.clear();
        getline(fntStream, sFntLine);
        split(sFntElems, sFntLine, is_space());
        font->mGlyphCount = lexical_cast<int>(ReadFntPair(sFntElems[1]).second.c_str());

        // NOTE(Wuxiang): Unicode Codepoint range: http://inamidst.com/stuff/unidata/
        // U+4E00 to U+9FFF: CJK Unified Ideographs
        // U+A000 to U+A48F: Yi Syllables
        static const int sMaxCodepointPastOne = 0xA000;

        // Allocate storage for index table. This member would be large. The default
        // value refers to the none character, which has id = 0. This character is
        // always loaded first.
        font->mGlyphIndexTable.assign(sMaxCodepointPastOne, 0);

        // Read every glyph
        boost::regex spaceMultiple("[ ]+");
        string space = " ";

        for (size_t fontGlyphIndex = 0; fontGlyphIndex < font->mGlyphCount; ++fontGlyphIndex)
        {
            sFntElems.clear();
            getline(fntStream, sFntLine);

            // Replace multiple space with single space to avoid splitting error.
            sFntLine = regex_replace(sFntLine, spaceMultiple, space);

            split(sFntElems, sFntLine, is_space());

            LoadFntGlyphLine(*font, sFntElems, fontGlyphIndex, fontGlyphPT, fontGlyphPR, fontGlyphPB, fontGlyphPL);
        }
    }

    fntStream.close();

    font->SetSize(fontSize);
    return unique_ptr<BitmapFont>(font);
}

BitmapFontUniquePtr
AssetProcessor::LoadRawFont(const std::string& fntFilePath)
{
    if (Exist(fntFilePath))
    {
        auto font = LoadFntFile(fntFilePath);
        return font;
    }

    return nullptr;
}

void
AssetProcessor::BakeTexture2d(const std::string& textureFilePath)
{
    if (GetFileExtension(textureFilePath) != u8".png")
    {
        FALCON_ENGINE_NOT_SUPPORT();
    }

    auto textureHandle = LoadRawTexture2d(textureFilePath);
    BakeTexture2d(textureHandle.get(), AddAssetExtension(textureFilePath));
}

void
AssetProcessor::BakeTexture2d(Texture2d *texture, const string& textureOutputPath)
{
    // http://stackoverflow.com/questions/24313359/data-dependent-failure-when-serializing-stdvector-to-boost-binary-archive
    ofstream textureAssetStream(textureOutputPath, ios::binary);
    archive::binary_oarchive textureAssetArchive(textureAssetStream);
    textureAssetArchive << *texture;
}

std::unique_ptr<Texture2d>
AssetProcessor::LoadRawTexture2d(const std::string& textureFilePath)
{
    // NOTE(Wuxiang): Since the stb_image default loading format goes from top-left to bottom-right,
    // it is necessary to flip to make it compatible for OpenGL.
    stbi_set_flip_vertically_on_load(1);

    int  textureDimension[3];
    int  textureChannel;
    auto textureData = stbi_load(textureFilePath.c_str(), &textureDimension[0],
                                 &textureDimension[1], &textureChannel,
                                 STBI_rgb_alpha);
    if (textureData == nullptr)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Failed to load texture file.");
    }

    // NOTE(Wuxiang): Copy the memory allocated from the stb library.
    auto *texture = new Texture2d(GetFileStem(textureFilePath), textureFilePath, textureDimension[0], textureDimension[1], TextureFormat::R8G8B8A8);
    texture->mFileType = AssetSource::Stream;
    memcpy(texture->mData, textureData, texture->mDataByteNum);
    stbi_image_free(textureData);

    return unique_ptr<Texture2d>(texture);
}

void
BakeMaterial(aiMaterial               *material,
             aiTextureType             textureType,
             std::vector<std::string>& texturePathsBaked)
{
    for (unsigned int textureIndex = 0; textureIndex < material->GetTextureCount(textureType); ++textureIndex)
    {
        aiString textureFilePath;
        material->GetTexture(textureType, textureIndex, &textureFilePath);
        auto textureFilePathString = string(textureFilePath.C_Str());

        // When we find this ready to load texture has been loaded already
        auto iter = find(texturePathsBaked.begin(), texturePathsBaked.end(), textureFilePathString);
        if (iter != texturePathsBaked.end())
        {
            continue;
        }
        else
        {
            AssetProcessor::BakeTexture2d(textureFilePathString);
            texturePathsBaked.push_back(textureFilePathString);
        }
    }
}

void
AssetProcessor::BakeModel(const std::string& modelFilePath)
{
    // Load model using Assimp
    static Assimp::Importer modelImporter;
    const aiScene *scene = modelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        FALCON_ENGINE_THROW_EXCEPTION(modelImporter.GetErrorString());
    }

    // Bake texture in model
    vector<string> texturePathsBaked;
    for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
    {
        auto material = scene->mMaterials[materialIndex];

        BakeMaterial(material, aiTextureType_AMBIENT, texturePathsBaked);
        BakeMaterial(material, aiTextureType_DIFFUSE, texturePathsBaked);
        BakeMaterial(material, aiTextureType_EMISSIVE, texturePathsBaked);
        BakeMaterial(material, aiTextureType_SHININESS, texturePathsBaked);
        BakeMaterial(material, aiTextureType_SPECULAR, texturePathsBaked);
    }

    // We don't need to get the fully initialized model at processor. The model
    // is only half loaded.
}

}
#endif