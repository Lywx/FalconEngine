#pragma once

#include "TextMesh.h"

/**
    Represents a font. It holds the font's texture atlas as well as having the
    ability to create the quad vertices for any text using this font.

    @author Karl

*/

// Represents a font.
class FontType
{
    /**
        Creates a new font and loads up the data about each character from the
        font file.

        @param fontFile
                 - the font file containing information about each character in
                 the texture atlas.
    */
public:

    FontType(int textureAtlas)
    {
        m_textureAtlasId = textureAtlas;
    }

    int getTextureAtlas()
    {
        return m_textureAtlasId;
    }

    /**
        Takes in an unloaded text and calculate all of the vertices for the quads
        on which this text will be rendered. The vertex positions and texture
        coords and calculated based on the information from the font file.

        @param text
                 - the unloaded text.
        @return Information about the vertices of all the quads.
    */
    TextMeshData loadText(GUIText text)
    {
        return loader.createTextMesh(text);
    }

private:
    int m_textureAtlasId;
};
