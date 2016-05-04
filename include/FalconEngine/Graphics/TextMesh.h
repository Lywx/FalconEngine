#pragma once

#include <vector>

#include <FalconEngine/Graphics/Mesh.h>

namespace FalconEngine {

/**
    Stores the vertex data for all the quads on which a text will be rendered.
    @author Karl
*/
struct TextMeshData
{
    TextMeshData()
        : VertexPosition(new VertexList())
        , TexturePosition(new TextureList())
    {
    }

    VertexList *VertexPosition;
    size_t      VertexCount() const { return VertexPosition->size(); }

    TextureList *TexturePosition;
    size_t       TexturePositionCount() const { return TexturePosition->size(); }
};

}
