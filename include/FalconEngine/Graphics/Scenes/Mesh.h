#pragma once

#include <FalconEngine/Graphics/GraphicsInclude.h>

#include <vector>

#include <assimp/scene.h>

#include <FalconEngine/Graphics/Renderers/VisualTriangles.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>

namespace FalconEngine
{

class Model;
class Mesh : public VisualTriangles
{
    FALCON_ENGINE_RTTI_DECLARE;

public:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    // @summary Load vertex, normal, texture coordinate, index, texture object.
    Mesh(Model *model, const aiScene *scene, const aiMesh *mesh);
    virtual ~Mesh();

protected:
    void
    LoadBuffers(const aiMesh *mesh);

    void
    LoadTextures(Model *model, const aiScene *scene, const aiMesh *mesh);

    // @param model - the model owns this mesh.
    // @param material - the material to load from.
    // @param materialTextureIndexVector - index of material's texture into the model's texture vector.
    // @param materialTextureType - the texture type to load from.
    void
    LoadMaterialTexture(Model               *model,
                        const aiMaterial    *material,
                        std::vector<size_t>& materialTextureIndexVector,
                        aiTextureType        materialTextureType);

    std::vector<size_t>  mTextureIndexVector; // Texture used in this mesh, in term of index into the model texture vector.
};

typedef std::shared_ptr<Mesh> MeshSharedPtr;

}
