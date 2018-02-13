#pragma once

#include <FalconEngine/Core/Macro.h>

#include <FalconEngine/Content/CerealLibGuardBegin.h>
#include <cereal/access.hpp>

namespace FalconEngine
{
// @summary This represents a glyph in bitmap. The information related to the
// font it's using and the size of that font.
class FALCON_ENGINE_API FontGlyph
{
public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    FontGlyph();
    FontGlyph(int id, double width, double height, double offsetX,
              double offsetY, double advance, int page, double s1, double t1,
              double s2, double t2);

public:
    /************************************************************************/
    /* Asset Importing and Exporting                                        */
    /************************************************************************/
    friend class cereal::access;
    template <typename Archive>
    void serialize(Archive & ar)
    {
        // NOTE(Wuxiang): Since this class doesn't have default constructor. The
        // serialization code is moved to below.
        ar & mId;
        ar & mPage;

        ar & mWidth;
        ar & mHeight;

        ar & mOffsetX;
        ar & mOffsetY;
        ar & mAdvance;

        ar & mS1;
        ar & mT1;
        ar & mS2;
        ar & mT2;
    }

    template <class Archive>
    static void load_and_construct(Archive & ar, cereal::construct<FontGlyph> & construct)
    {
        int id, page;
        ar & id;
        ar & page;

        double width, height;
        ar & width;
        ar & height;

        double offsetX, offsetY, advance;
        ar & offsetX;
        ar & offsetY;
        ar & advance;

        double s1, t1, s2, t2;
        ar & s1;
        ar & t1;
        ar & s2;
        ar & t2;

        construct(id, width, height, offsetX,
                  offsetY, advance, page, s1, t1, s2, t2);
    }

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
};
}