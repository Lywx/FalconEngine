#include <FalconEngine/Graphics/Scenes/Mesh.h>
#include <FalconEngine/Graphics/Scenes/Model.h>
#include <FalconEngine/Graphics/Renderers/Texture2d.h>

using namespace std;

namespace FalconEngine
{

Mesh::Mesh()
    : m_vertexBuffer(nullptr),
      m_indexBuffer(nullptr)
{
}

Mesh::Mesh(Model *model, aiScene *scene, aiMesh *mesh)
    : Mesh()
{
    vector<Vertex> *vertexVector = new vector<Vertex>();
    vector<Index> *indexVector = new vector<Index>();

    // TODO(Wuxiang): Haven't figure out the texture buffer implementation
    vector<Texture2dPtr> *textureVector = new vector<Vertex>();

    for (size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex   vertex;
        Vector3f vec3;
        Vector2f vec2;

        // Position
        vec3.x = mesh->mVertices[i].x;
        vec3.y = mesh->mVertices[i].y;
        vec3.z = mesh->mVertices[i].z;
        vertex.m_position = vec3;

        // Normals
        vec3.x = mesh->mNormals[i].x;
        vec3.y = mesh->mNormals[i].y;
        vec3.z = mesh->mNormals[i].z;
        vertex.m_normal = vec3;

        // Texture
        if (mesh->mTextureCoords[0])
        {
            // NOTE(Wuxiang): A vertex can contain up to 8 different texture
            // coordinates.
            vec2.x = mesh->mTextureCoords[0][i].x;
            vec2.y = mesh->mTextureCoords[0][i].y;
            vertex.m_texCoords = vec2;
        }
        else
        {
            vertex.m_texCoords = vec2;
        }

        vertexVector->push_back(vertex);
    }

    // Walk through each of the mesh's faces (a face is a mesh its triangle)
    // and retrieve the corresponding vertex indexes.
    for (size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indexVector.push_back(face.mIndices[j]);
        }
    }

    // Walk through each of the material and retrieve the corresponding
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // We assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
        // Same applies to other texture as the following list summarizes:
        // Diffuse: texture_diffuseN
        // Specular: texture_specularN
        // Normal: texture_normalN

        // Diffuse maps
        static vector<Texture> diffuseMapTextureGroup;
        LoadMaterial(model, diffuseMapTextureGroup, material, aiTextureType_DIFFUSE, "texture_diffuse");
        textureVector.insert(textureVector.end(), diffuseMapTextureGroup.begin(), diffuseMapTextureGroup.end());

        // Specular maps
        static vector<Texture> specularMapTextureGroup;
        LoadMaterial(model, specularMapTextureGroup, material, aiTextureType_SPECULAR, "texture_specular");
        textureVector.insert(textureVector.end(), specularMapTextureGroup.begin(), specularMapTextureGroup.end());
    }

    m_vertexBuffer = make_shared<VertexBuffer>(vertexVector->size(), 3, sizeof(float), BufferUsage::Static);
    m_vertexBuffer->m_data = reinterpret_cast<char *>(&vertexVector[0]);
    m_vertexBuffer->m_dataContainer = vertexVector;

    m_indexBuffer = make_shared<IndexBuffer>(indexVector->size(), sizeof(Index), BufferUsage::Static);
    m_indexBuffer->m_data = reinterpret_cast<char *>(&indexVector[0]);
    m_vertexBuffer->m_dataContainer = indexVector;
}

void
Mesh::LoadMaterial(Model           *model,
                   vector<Texture>& materialTextureGroup,
                   aiMaterial      *material,
                   aiTextureType    textureType,
                   string           textureTypeName)
{
    vector<Texture> textures;
    for (GLuint materialIndex = 0; materialIndex < material->GetTextureCount(textureType); ++materialIndex)
    {
        aiString textureFilePath;
        material->GetTexture(textureType, materialIndex, &textureFilePath);

        bool skip = false;

        // Linear search loaded texture
        for (GLuint textureIndex = 0; textureIndex < model->m_textureVector.size(); textureIndex++)
        {
            auto texture = model->m_textureVector[textureIndex];

            // When we find this ready to load texture has been loaded already
            if (texture->m_textureFilePath.c_str() == textureFilePath.C_Str())
            {
                textures.push_back(model->m_textureVector[textureIndex]->m_id);
                skip = true;
                break;
            }
        }

        if (!skip)
        {
            auto textureResource = make_shared<Texture2d>();
            textureResource->LoadFromAssetFile(textureFilePath.C_Str());
            textures.push_back(textureResource);
            model->m_textureVector.push_back(textureResource);
        }
    }
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::~Mesh()
{
}

}
