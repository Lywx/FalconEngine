#pragma once

#include <vector>
#include <assimp/scene.h>

#include <FalconEngine/Graphics/Renderers/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Texture2d.h>
#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine
{

struct Vertex
{
    Vector3f m_position;
    Vector3f m_normal;
    Vector2f m_texCoords;
};

class Model;
class Mesh : public Spatial
{
protected:
    Mesh();

public:

    // @Summary: Load vertex, normal, texture coordinate, index, texture object,
    //
    Mesh(Model *model, aiScene *scene, aiMesh *mesh);
    virtual ~Mesh();

    void
    LoadMaterial(Model                *model,
                 std::vector<Texture>& materialTextureGroup,
                 aiMaterial           *material,
                 aiTextureType         textureType,
                 std::string           textureTypeName);

public:
    VertexBufferPtr           m_vertexBuffer;
    IndexBufferPtr            m_indexBuffer;
};

typedef std::shared_ptr<Mesh> MeshPtr;

}
