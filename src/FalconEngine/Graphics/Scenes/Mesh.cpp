#include <FalconEngine/Graphics/Scenes/Mesh.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Scenes/Model.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(Mesh, VisualTriangles);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
Mesh::Mesh(Model *model, const aiScene *scene, const aiMesh *mesh) :
    VisualTriangles(nullptr, nullptr)
{
    LoadBuffers(mesh);
    LoadTextures(model, scene, mesh);
}

void
Mesh::LoadBuffers(const aiMesh *mesh)
{
    // Fill vertex buffer.
    {
        // Memory allocation for vertex buffer.
        int vertexNum = mesh->mNumVertices;
        auto vertexBuffer = std::make_shared<VertexBuffer>(vertexNum, sizeof(ModelVertex), BufferUsage::Static);
        auto vertexes = reinterpret_cast<ModelVertex *>(vertexBuffer->mData);

        // Walk through vertex data and create vertex buffer content in an interlaced fashion.
        for (size_t i = 0; i < mesh->mNumVertices; ++i)
        {
            ModelVertex vertex;
            Vector3f vec3;
            Vector2f vec2;

            // Position
            vec3.x = mesh->mVertices[i].x;
            vec3.y = mesh->mVertices[i].y;
            vec3.z = mesh->mVertices[i].z;
            vertex.mPosition = vec3;

            // Normal
            vec3.x = mesh->mNormals[i].x;
            vec3.y = mesh->mNormals[i].y;
            vec3.z = mesh->mNormals[i].z;
            vertex.mNormal = vec3;

            // Texture coordinate
            if (mesh->mTextureCoords[0])
            {
                // NOTE(Wuxiang): A vertex can contain up to 8 different texture
                // coordinates.
                vec2.x = mesh->mTextureCoords[0][i].x;
                vec2.y = mesh->mTextureCoords[0][i].y;
                vertex.mTexCoord = vec2;
            }
            else
            {
                vertex.mTexCoord = Vector2f::Zero;
            }

            // NOTE(Wuxiang):
            vertexes[i] = vertex;
        }

        // TODO(Wuxiang): Should I change the binding index?
        mVertexFormat->PushVertexBuffer(0, vertexBuffer, 0, sizeof(ModelVertex));
        mCount = vertexNum;
    }

    // Fill index buffer.
    {
        // Sum space for the index buffer memory allocation.
        int indexNum = 0;
        {
            for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
            {
                indexNum += mesh->mFaces[faceIndex].mNumIndices;
            }
        }

        // Memory allocation for index buffer.
        mIndexBuffer = std::make_shared<IndexBuffer>(indexNum, IndexType::UnsignedInt, BufferUsage::Static);
        auto indexes = reinterpret_cast<ModelIndex *>(mIndexBuffer->mData);

        // Walk through each of the mesh's faces (a face is a mesh its triangle)
        // and retrieve the corresponding vertex indexes.
        {
            int indexNumAdded = 0;
            for (unsigned int faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex)
            {
                auto& face = mesh->mFaces[faceIndex];
                for (unsigned int j = 0; j < face.mNumIndices; j++)
                {
                    indexes[indexNumAdded] = face.mIndices[j];
                    ++indexNumAdded;
                }
            }
        }
    }
}

void
Mesh::LoadTextures(Model *model, const aiScene *scene, const aiMesh *mesh)
{
    // Walk through each of the material and retrieve the corresponding textures.
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        // TODO(Wuxiang 2017-01-27 16:02): Add ambient.

        // Load diffuse maps
        static vector<size_t> diffuseMapTextureIndexVector;
        diffuseMapTextureIndexVector.clear();
        LoadMaterialTexture(model, material, diffuseMapTextureIndexVector, aiTextureType_DIFFUSE);
        mTextureIndexVector.insert(mTextureIndexVector.end(), diffuseMapTextureIndexVector.begin(), diffuseMapTextureIndexVector.end());

        // Load specular maps
        static vector<size_t> specularMapTextureIndexVector;
        specularMapTextureIndexVector.clear();
        LoadMaterialTexture(model, material, specularMapTextureIndexVector, aiTextureType_SPECULAR);
        mTextureIndexVector.insert(mTextureIndexVector.end(), specularMapTextureIndexVector.begin(), specularMapTextureIndexVector.end());
    }
}

void
Mesh::LoadMaterialTexture(Model            *model,
                          const aiMaterial *material,
                          vector<size_t>&   materialTextureIndexVector,
                          aiTextureType     materialTextureType)
{
    int textureNum = material->GetTextureCount(materialTextureType);
    if (textureNum > 0)
    {
        auto assetManager = AssetManager::GetInstance();

        // Walk through every piece of material and load texture if needed
        for (int textureIndex = 0; textureIndex < textureNum; ++textureIndex)
        {
            aiString textureFilePath;
            material->GetTexture(materialTextureType, textureIndex, &textureFilePath);

            // Linear search loaded texture
            bool textureFound = false;
            {
                for (int textureIndexLoaded = 0; textureIndexLoaded < model->mTextureVector.size(); textureIndexLoaded++)
                {
                    auto textureLoaded = model->mTextureVector[textureIndexLoaded];

                    // When we find this ready to load texture has been loaded already
                    if (textureLoaded->mFilePath.c_str() == textureFilePath.C_Str())
                    {
                        // Add the
                        materialTextureIndexVector.push_back(textureIndexLoaded);
                        textureFound = true;
                        break;
                    }
                }
            }

            if (!textureFound)
            {
                auto texture = assetManager->LoadTexture2d(textureFilePath.C_Str());
                materialTextureIndexVector.push_back(materialTextureIndexVector.size());
                model->mTextureVector.push_back(texture);
            }
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
