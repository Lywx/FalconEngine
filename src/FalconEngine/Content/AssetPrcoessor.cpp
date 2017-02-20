#include <FalconEngine/Content/AssetProcessor.h>

#if FALCON_ENGINE_OS_WINDOWS
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
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
/* Constructors and Destructor                                          */
/************************************************************************/
AssetProcessor::AssetProcessor()
{
}

AssetProcessor::~AssetProcessor()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
AssetProcessor::BakeFont(std::string fntFilePath)
{
    auto fontHandle = LoadRawFont(fntFilePath);
    if (fontHandle)
    {
        auto fontOuptutPath = ChangeFileExtension(fntFilePath, u8".bin");
        BakeFont(fontHandle.get(), fontOuptutPath);

        // Bake font's textures
        auto fntDirPath = GetFileDirectory(fntFilePath);
        for (int fontPageId = 0; fontPageId < fontHandle->mTexturePages; ++fontPageId)
        {
            auto textureFilePath = fntDirPath + fontHandle->mTextureFileNameVector[fontPageId];
            auto texture = LoadRawTexture2d(textureFilePath);
            BakeTexture2d(texture.get(), ChangeFileExtension(textureFilePath, u8".bin"));
        }
    }
}

void
AssetProcessor::BakeFont(BitmapFont *font, std::string fontOutputPath)
{
    ofstream fontAssetStream(fontOutputPath);
    archive::binary_oarchive fontAssetArchive(fontAssetStream);
    fontAssetArchive << *font;
}

// TODO(Wuxiang 2016-12-30 19:13): Move this to texture paramter?
//GLuint fontTextureObject;
//glGenTextures(1, &fontTextureObject);
//glBindTexture(GL_TEXTURE_2D_ARRAY, fontTextureObject);
//glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, font->mTextureWidth, font->mTextureHeight, font->mTexturePages);
//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

pair<string, string>
ReadFntPair(const string fntPair)
{
    static vector<string> lineElems;
    lineElems.clear();

    split(lineElems, fntPair, is_any_of("="));
    return make_pair(lineElems[0], lineElems[1]);
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
    static map<string, string> fontGlyphPairTable;

    // Skip "char", the first element
    for (size_t i = 1; i < fontGlyphElems.size(); ++i)
    {
        if (fontGlyphElems[i].size() != 0)
        {
            pair<string, string> keyValuePair = ReadFntPair(fontGlyphElems[i]);
            fontGlyphPairTable[keyValuePair.first] = keyValuePair.second;
        }
    }

    // Total horizontal padding
    int fontGlyphPWidth = fontGlyphPL + fontGlyphPR;

    // NOTE(Wuxiang): The fnt file has to configured to padding = 0 in all directions.
    int id = lexical_cast<int>(fontGlyphPairTable.at("id").c_str());
    double width = lexical_cast<double>(fontGlyphPairTable.at("width").c_str());
    double height = lexical_cast<double>(fontGlyphPairTable.at("height").c_str());

    // NOTE(Wuxiang): Only amend padding data in vertex related data. Texture quad
    // should be expanded as the padding expands.
    double offsetX = lexical_cast<double>(fontGlyphPairTable.at("xoffset").c_str()) + fontGlyphPL;
    double offsetY = lexical_cast<double>(fontGlyphPairTable.at("yoffset").c_str()) + fontGlyphPT;
    double advance = lexical_cast<double>(fontGlyphPairTable.at("xadvance").c_str()) - fontGlyphPWidth;

    // NOTE(Wuxiang): The fnt file x, y represents left and top pixel coordinate
    // origined from top-left corner of the png file. However, in opengl s1, t1
    // represents left and bottom coordinate origined from bottom-left corner of
    // the screen.
    double s1 = lexical_cast<double>(fontGlyphPairTable.at("x").c_str()) / font.mTextureWidth;
    double s2 = s1 + width / font.mTextureWidth;
    double t2 = (font.mTextureHeight - lexical_cast<double>(fontGlyphPairTable.at("y").c_str())) / font.mTextureHeight;
    double t1 = t2 - height / font.mTextureHeight;

    int page = lexical_cast<int>(fontGlyphPairTable.at("page").c_str());

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
    static map<string, string> fontPagePairs;

    // Skip "page", the first element
    for (size_t i = 1; i < fontPageElems.size(); ++i)
    {
        if (fontPageElems[i].size() != 0)
        {
            pair<string, string> keyValuePair = ReadFntPair(fontPageElems[i]);
            fontPagePairs[keyValuePair.first] = keyValuePair.second;
        }
    }

    auto fontTextureFileName = trim_copy_if(fontPagePairs.at("file"), is_any_of("\""));
    font.mTextureFileNameVector.push_back(fontTextureFileName);
    font.mTextureArchiveNameVector.push_back(ChangeFileExtension(fontTextureFileName, u8".bin"));
}

// @Return: whether should continue reading texture file. If you should, the
// pointer points to the half loaded font.
std::unique_ptr<BitmapFont>
LoadFntFile(std::string fntFilePath)
{
    static vector<string> fntElems;
    static string         fntLine;
    ifstream              fntStream;

    // Try open fnt file.
    fntStream.open(fntFilePath);
    if (!fntStream.good())
    {
        ThrowRuntimeException("Failed to load fnt file.");
    }

    static map<string, string> fontSettingTable;
    fontSettingTable.clear();

    // Read first 2 lines of font metadata
    {
        // 1st line. Since the face name could contain space character, we need to
        // process this line separately
        {
            getline(fntStream, fntLine);

            auto faceLhsQuote = find_nth(fntLine, "\"", 0);
            auto faceRhsQuote = find_nth(fntLine, "\"", 1);
            auto faceLength = distance(faceLhsQuote.begin(), faceRhsQuote.begin());
            auto faceNameIndex = distance(fntLine.begin(), faceLhsQuote.begin()) + 1;
            auto faceSettingIndex = distance(fntLine.begin(), faceLhsQuote.begin()) - 5;
            auto sizeSettingIndex = distance(fntLine.begin(), faceRhsQuote.begin()) + 2;

            fontSettingTable["face"] = fntLine.substr(faceNameIndex, faceLength);
            fntLine.erase(faceSettingIndex, sizeSettingIndex - faceSettingIndex);
            split(fntElems, fntLine, is_space());
            PushFntMetaLine(fontSettingTable, fntElems);
        }

        // 2nd line
        fntElems.clear();
        getline(fntStream, fntLine);
        split(fntElems, fntLine, is_space());

        PushFntMetaLine(fontSettingTable, fntElems);
    }

    // Create font
    auto font = new BitmapFont(GetFileStem(fntFilePath), fntFilePath);

    // Read page number and read page specific filename
    font->mTexturePages = lexical_cast<int>(fontSettingTable.at("pages"));
    for (int i = 0; i < font->mTexturePages; ++i)
    {
        fntElems.clear();
        getline(fntStream, fntLine);
        split(fntElems, fntLine, is_space());

        LoadFntPageLine(*font, fntElems);
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
        fontSize = lexical_cast<int>(fontSettingTable.at("size"));
        font->mLineBase = lexical_cast<uint32>(fontSettingTable.at("base"));
        font->mLineHeight = lexical_cast<uint32>(fontSettingTable.at("lineHeight"));
        font->mTextureWidth = lexical_cast<int>(fontSettingTable.at("scaleW"));
        font->mTextureHeight = lexical_cast<int>(fontSettingTable.at("scaleH"));

        fntElems.clear();
        auto& glyphPaddingString = fontSettingTable.at("padding");
        trim(glyphPaddingString);
        split(fntElems, glyphPaddingString, is_any_of(","));

        fontGlyphPT = lexical_cast<int>(fntElems[0]);
        fontGlyphPR = lexical_cast<int>(fntElems[1]);
        fontGlyphPB = lexical_cast<int>(fntElems[2]);
        fontGlyphPL = lexical_cast<int>(fntElems[3]);
    }

    // Read character glyphs
    {
        // Read glyph number
        fntElems.clear();
        getline(fntStream, fntLine);
        split(fntElems, fntLine, is_space());
        font->mGlyphCount = lexical_cast<int>(ReadFntPair(fntElems[1]).second.c_str());

        // NOTE(Wuxiang): Unicode Codepoint range: http://inamidst.com/stuff/unidata/
        // U+4E00 to U+9FFF: CJK Unified Ideographs
        // U+A000 to U+A48F: Yi Syllables
        static const int MaxCodepointPastOne = 0xA000;

        // Allocate storage for index table. This member would be large. The default
        // value refers to the none character, which has id = 0. This character is
        // always loaded first.
        font->mGlyphIndexTable.assign(MaxCodepointPastOne, 0);

        // Read every glyph
        boost::regex spaceMultiple("[ ]+");
        string space = " ";

        for (size_t fontGlyphIndex = 0; fontGlyphIndex < font->mGlyphCount; ++fontGlyphIndex)
        {
            fntElems.clear();
            getline(fntStream, fntLine);

            // Replace multiple space with single space to avoid splitting error.
            fntLine = regex_replace(fntLine, spaceMultiple, space);

            split(fntElems, fntLine, is_space());

            LoadFntGlyphLine(*font, fntElems, fontGlyphIndex, fontGlyphPT, fontGlyphPR, fontGlyphPB, fontGlyphPL);
        }
    }

    fntStream.close();

    font->SetSize(fontSize);
    return unique_ptr<BitmapFont>(font);
}

BitmapFontUniquePtr
AssetProcessor::LoadRawFont(std::string fntFilePath)
{
    if (Exist(fntFilePath))
    {
        auto font = LoadFntFile(fntFilePath);
        return font;
    }

    return nullptr;
}

void
AssetProcessor::BakeTexture2d(std::string textureFilePath)
{
    auto textureHandle = LoadRawTexture2d(textureFilePath);
    BakeTexture2d(textureHandle.get(), ChangeFileExtension(textureFilePath, u8".bin"));
}

void
AssetProcessor::BakeTexture2d(Texture2d *texture, string textureOutputPath)
{
    ofstream textureAssetStream(textureOutputPath);
    archive::binary_oarchive textureAssetArchive(textureAssetStream);
    textureAssetArchive << *texture;
}

std::unique_ptr<Texture2d>
AssetProcessor::LoadRawTexture2d(std::string textureFilePath)
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
        ThrowRuntimeException("Failed to load texture file.");
    }

    // NOTE(Wuxiang): Copy the memory allocated from the stb library.
    auto *texture = new Texture2d(GetFileStem(textureFilePath), textureFilePath, textureDimension[0], textureDimension[1], TextureFormat::R8G8B8A8);
    texture->mFileType = AssetSource::Stream;
    memcpy(texture->mData, textureData, texture->mDataByteNum);
    stbi_image_free(textureData);

    return unique_ptr<Texture2d>(texture);
}

void
AssetProcessor::BakeModel(std::string modelFilePath)
{
    // Load model using Assimp
    static Assimp::Importer modelImporter;
    const aiScene *scene = modelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        ThrowRuntimeException(modelImporter.GetErrorString());
    }

    // Bake texture in model
    vector<string> texturePathsBaked;
    for (unsigned int materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex)
    {
        auto material = scene->mMaterials[materialIndex];

        BakeMaterial(material, aiTextureType_AMBIENT, texturePathsBaked);
        BakeMaterial(material, aiTextureType_DIFFUSE, texturePathsBaked);
        BakeMaterial(material, aiTextureType_SPECULAR, texturePathsBaked);
    }

    // We don't need to get the fully initialized model at processor. The model
    // is only half loaded.
}

void
AssetProcessor::BakeMaterial(aiMaterial               *material,
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
            BakeTexture2d(textureFilePathString);
            texturePathsBaked.push_back(textureFilePathString);
        }
    }
}

}
#endif