#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>

#include <FalconEngine/Content/Asset.h>
#include <FalconEngine/Graphics/Renderers/BitmapGlyph.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderers/Resources/Sampler.h>

namespace FalconEngine
{

// @summary Bitmap font store the unmodified information in the imported bitmap
// font. In the rendering phrase, the font size is used with the bitmap glyph
// size to derive desired glyph size. The size stores imported bmfont size. So as
// the line base, line height, space width, etc.
class BitmapFont : public Asset
{
public:
    FALCON_ENGINE_RTTI_DECLARE;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BitmapFont(const std::string& fileName, const std::string& filePath);
    virtual ~BitmapFont();

public:
    /************************************************************************/
    /* Font Runtime Data -- Glyph (1/2)                                     */
    /************************************************************************/

    // NOTE(Wuxiang): Not serialized members include: mSizeScale, mTexture. mTexture,
    // which is texture array, is composited during loading using multiple textures.

    double                        mSizePt = 0;                                 // Font size in point.
    double                        mSizePx = 0;                                 // Font size in pixel.

    static double const           mSizeScale;                                  // Font size up-scaling factor based on test result.

    double                        mLineBase = 0;                               // Font base height in pixel.
    double                        mLineHeight = 0;                             // Font line height (em height) in pixel.

    size_t                        mGlyphCount = 0;                             // Font glyph number the font contains
    std::vector<size_t>           mGlyphIndexTable;                            // Font glyph index table that map glyph Codepoint into glyph's index in glyph table.
    std::vector<BitmapGlyph>      mGlyphTable;

    /************************************************************************/
    /* Font Metadata                                                        */
    /************************************************************************/
    int                           mTextureWidth;
    int                           mTextureHeight;
    int                           mTexturePages;                               // Font texture page number

    std::vector<std::string>      mTextureArchiveNameVector;                   // Font raw texture filenames, index is the page id
    std::vector<std::string>      mTextureFileNameVector;                      // Font texture archive filenames, index is the page id

    void
    SetSize(double size)
    {
        mSizePt = size / mSizeScale;
        mSizePx = mSizePt / 72 * 96;
    }

    void
    SetSampler(SamplerSharedPtr sampler)
    {
        mSampler = sampler;
    }

    const Sampler *
    GetSampler() const
    {
        return mSampler.get();
    }

    void
    SetTexture(Texture2dArraySharedPtr texture)
    {
        mTexture = texture;
    }

    const Texture2dArray *
    GetTexture() const
    {
        return mTexture.get();
    }

private:
    /************************************************************************/
    /* Font Runtime Data -- Texture (2/2)                                   */
    /************************************************************************/

    // NOTE(Wuxiang): The reason texture array is in form of shared_ptr is that
    // the texture array could not be reused anywhere so that it is better to
    // dispose of the texture array when font is destroyed. However, individual
    // textures would not be destroyed since texture array is just a container.

    Texture2dArraySharedPtr       mTexture;                                    // Font texture.
    SamplerSharedPtr              mSampler;                                    // Font texture sampler.

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
public:
    friend class boost::serialization::access;
    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        ar << boost::serialization::base_object<const Asset>(*this);

        ar << mSizePt;
        ar << mSizePx;

        ar << mLineBase;
        ar << mLineHeight;

        ar << mGlyphCount;
        ar << mGlyphIndexTable;
        ar << mGlyphTable;

        ar << mTextureWidth;
        ar << mTextureHeight;
        ar << mTexturePages;

        ar << mTextureArchiveNameVector;
        ar << mTextureFileNameVector;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        ar >> boost::serialization::base_object<Asset>(*this);

        ar >> mSizePt;
        ar >> mSizePx;

        ar >> mLineBase;
        ar >> mLineHeight;

        ar >> mGlyphCount;
        ar >> mGlyphIndexTable;
        ar >> mGlyphTable;

        ar >> mTextureWidth;
        ar >> mTextureHeight;
        ar >> mTexturePages;

        ar >> mTextureArchiveNameVector;
        ar >> mTextureFileNameVector;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
};

typedef std::shared_ptr<BitmapFont> BitmapFontSharedPtr;
typedef std::unique_ptr<BitmapFont> BitmapFontUniquePtr;

}
