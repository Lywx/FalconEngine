#pragma once

#include <FalconEngine/Core/Macro.h>

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <FalconEngine/Content/CerealLibGuardBegin.h>
#include <cereal/access.hpp>
#include <cereal/types/base_class.hpp>
// https://github.com/USCiLab/cereal/issues/286
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Graphics/Renderer/Font/FontGlyph.h>
#include <FalconEngine/Graphics/Renderer/Resource/Sampler.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>

namespace FalconEngine
{

// @summary This class implement Bitmap font, storing the unmodified information
// in the imported bitmap font. In the rendering phrase, the font size is used
// with the bitmap glyph size to derive desired glyph size. The size stores
// imported bmfont size. So as the line base, line height, space width, etc.
FALCON_ENGINE_CLASS_BEGIN Font :
public Asset
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    Font();
    Font(AssetSource assetSource, const std::string & fileName, const std::string & filePath);
    virtual ~Font();

public:
    void
    SetSize(double size);

    void
    SetSampler(std::unique_ptr<Sampler> sampler);

    const Sampler *
    GetSampler() const;

    void
    SetTexture(std::unique_ptr<Texture2dArray> texture);

    const Texture2dArray *
    GetTexture() const;

public:
    /************************************************************************/
    /* Font Runtime Data -- Glyph (1/2)                                     */
    /************************************************************************/

    // NOTE(Wuxiang): Not serialized members include: mSizeScale, mTexture. mTexture,
    // which is texture array, is composited during loading using multiple textures.

    // Font size in point.
    double mSizePt = 0;

    // Font size in pixel.
    double mSizePx = 0;

    // Font size up-scaling factor based on test result.
    static double const mSizeScale;

    // Font base height in pixel.
    double mLineBase = 0;

    // Font line height (em height) in pixel.
    double mLineHeight = 0;

    // Font glyph number the font contains
    size_t mGlyphCount = 0;

    // Font glyph index table that map glyph Codepoint into glyph's index in glyph table.
    std::vector<size_t> mGlyphIndexTable;
    std::vector<FontGlyph> mGlyphTable;

    /************************************************************************/
    /* Font Metadata                                                        */
    /************************************************************************/
    int mTextureWidth = 0;
    int mTextureHeight = 0;

    // Font texture page number
    int mTexturePages = 0;

    // Font raw texture filenames, index is the page id
    std::vector<std::string> mTextureArchiveNameList;

    // Font texture archive filenames, index is the page id
    std::vector<std::string> mTextureFileNameList;

private:
    /************************************************************************/
    /* Font Runtime Data -- Texture (2/2)                                   */
    /************************************************************************/

    // NOTE(Wuxiang): The reason texture array is in form of unique_ptr is that
    // the texture array could not be reused anywhere so that it is better to
    // dispose of the texture array when font is destroyed. Further more, individual
    // textures would not be destroyed because Texture2DArray class use shared_ptr
    // to manage Texture2D.

    // Font texture.
    std::unique_ptr<Texture2dArray> mTexture;

    // Font texture sampler.
    std::unique_ptr<Sampler> mSampler;

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive & ar)
    {
        ar & cereal::base_class<Asset>(this);

        ar & mSizePt;
        ar & mSizePx;

        ar & mLineBase;
        ar & mLineHeight;

        ar & mGlyphCount;
        ar & mGlyphIndexTable;
        ar & mGlyphTable;

        ar & mTextureWidth;
        ar & mTextureHeight;
        ar & mTexturePages;

        ar & mTextureArchiveNameList;
        ar & mTextureFileNameList;
    }
};
FALCON_ENGINE_CLASS_END

}

