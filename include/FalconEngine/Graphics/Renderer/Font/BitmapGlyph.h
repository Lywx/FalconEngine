#pragma once

#include <FalconEngine/Graphics/Header.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_member.hpp>

namespace FalconEngine
{
// @summary This represents a glyph in bitmap. The information related to the
// font it's using and the size of that font.
class BitmapGlyph
{
public:
    /************************************************************************/
    /* Lookup Data                                                          */
    /************************************************************************/
    int    mId;                                                              // glyph unicode codepoint
    int    mPage;                                                            // texture page id where the glyph image is found

    /************************************************************************/
    /* Vertex Data                                                          */
    /************************************************************************/
    double mWidth;                                                           // width of glyph in texture in pixels
    double mHeight;                                                          // height of glyph in texture in pixels

    double mOffsetX;
    double mOffsetY;
    double mAdvance;

    /************************************************************************/
    /* Texture Data                                                         */
    /************************************************************************/
    double mS1;
    double mT1;
    double mS2;
    double mT2;

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    BitmapGlyph(int id, double width, double height, double offsetX,
                double offsetY, double advance, int page, double s1, double t1,
                double s2, double t2);

    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class boost::serialization::access;
    template <typename TArchive>
    inline void serialize(TArchive & /* ar */, const unsigned int /* version */)
    {
        // NOTE(Wuxiang): Since this class doesn't have default constructor. The
        // serialization code is moved to below.
        //
        // http://www.boost.org/doc/libs/1_63_0/libs/serialization/doc/
    }
};

}

namespace boost
{
namespace serialization
{
template<class Archive>
inline void save_construct_data(
    Archive & ar, const FalconEngine::BitmapGlyph *t, const unsigned int /* version */)
{
    ar << t->mId;
    ar << t->mPage;

    ar << t->mWidth;
    ar << t->mHeight;

    ar << t->mOffsetX;
    ar << t->mOffsetY;
    ar << t->mAdvance;

    ar << t->mS1;
    ar << t->mT1;
    ar << t->mS2;
    ar << t->mT2;
}

template<class Archive>
inline void load_construct_data(
    Archive & ar, FalconEngine::BitmapGlyph *t, const unsigned int /* version */)
{
    int id, page;
    ar >> id;
    ar >> page;

    double width, height;
    ar >> width;
    ar >> height;

    double offsetX, offsetY, advance;
    ar >> offsetX;
    ar >> offsetY;
    ar >> advance;

    double s1, t1, s2, t2;
    ar >> s1;
    ar >> t1;
    ar >> s2;
    ar >> t2;

    ::new(t) FalconEngine::BitmapGlyph(id, width, height, offsetX,
                                       offsetY, advance, page, s1, t1, s2, t2);
}
}
}

