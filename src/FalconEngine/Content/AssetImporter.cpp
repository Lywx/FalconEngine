#include <FalconEngine/Content/AssetImporter.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Renderers/Resources/Buffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/Texture2d.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexFormat.h>
#include <FalconEngine/Graphics/Renderers/Resources/VertexGroup.h>
#include <FalconEngine/Graphics/Scene/Material.h>
#include <FalconEngine/Graphics/Scene/Mesh.h>
#include <FalconEngine/Graphics/Scene/Model.h>
#include <FalconEngine/Graphics/Scene/Node.h>

using namespace std;

namespace FalconEngine
{

VertexGroupSharedPtr
CreateModelVertexBuffer(const aiMesh *aiMesh)
{
    // Memory allocation for vertex buffer.
    int vertexNum = int(aiMesh->mNumVertices);
    auto vertexBuffer = std::make_shared<VertexBuffer>(vertexNum, sizeof(ModelVertex), BufferUsage::Static);
    auto vertexes = reinterpret_cast<ModelVertex *>(vertexBuffer->GetData());

    if (!aiMesh->mVertices)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Model doesn't have vertex data.");
    }

    if (!aiMesh->mNormals)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Model doesn't have normal data.");
    }

    if (!aiMesh->mTextureCoords)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Model doesn't have uv data.");
    }

    // Walk through vertex data and create vertex buffer content in an interlaced fashion.
    for (size_t i = 0; i < aiMesh->mNumVertices; ++i)
    {
        ModelVertex vertex;
        Vector3f vec3;
        Vector2f vec2;

        // Position
        vec3.x = aiMesh->mVertices[i].x;
        vec3.y = aiMesh->mVertices[i].y;
        vec3.z = aiMesh->mVertices[i].z;
        vertex.mPosition = vec3;

        // Normal
        vec3.x = aiMesh->mNormals[i].x;
        vec3.y = aiMesh->mNormals[i].y;
        vec3.z = aiMesh->mNormals[i].z;
        vertex.mNormal = vec3;

        // Texture coordinate
        if (aiMesh->mTextureCoords[0])
        {
            // NOTE(Wuxiang): A vertex can contain up to 8 different texture
            // coordinates.
            vec2.x = aiMesh->mTextureCoords[0][i].x;
            vec2.y = aiMesh->mTextureCoords[0][i].y;
            vertex.mTexCoord = vec2;
        }
        else
        {
            vertex.mTexCoord = Vector2f::Zero;
        }

        // NOTE(Wuxiang): The vertex data is interlaced.
        vertexes[i] = vertex;
    }

    // TODO(Wuxiang): Should I change the binding index?
    auto vertexGroup = make_shared<VertexGroup>();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, sizeof(ModelVertex));
    vertexGroup->SetVertexNum(vertexNum);
    return vertexGroup;
}

IndexBufferSharedPtr
CreateModelIndexBuffer(const aiMesh *mesh)
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
    auto indexBuffer = std::make_shared<IndexBuffer>(indexNum, IndexType::UnsignedInt, BufferUsage::Static);
    auto indexes = reinterpret_cast<ModelIndex *>(indexBuffer->GetData());

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

    return indexBuffer;
}

Texture2dSharedPtr
LoadMaterialTexture(
    _IN_     const aiMaterial *material,
    _IN_     aiTextureType     materialType)
{
    // NOTE(Wuxiang): I think most material only has one texture for each texture type.
    int textureNum = material->GetTextureCount(materialType);
    if (textureNum > 0)
    {
        auto assetManager = AssetManager::GetInstance();

        // Walk through every piece of material and load texture if needed
        for (int textureIndex = 0; textureIndex < textureNum; ++textureIndex)
        {
            // Read texture file path.
            aiString textureFilePath;
            material->GetTexture(materialType, textureIndex, &textureFilePath);

            // Get texture from asset manager without duplication using asset
            // manager's duplication checking mechanics.

            // NOTE(Wuxiang): Add .bin to file path so that the texture file is
            // loaded from preprocessed asset file.
            return assetManager->LoadTexture(AddAssetExtension(textureFilePath.C_Str()));
        }
    }

    return nullptr;
}

MaterialSharedPtr
CreateMaterial(
    _IN_      const aiScene *aiScene,
    _IN_      const aiMesh  *aiMesh)
{
    // When material exists.
    if (aiMesh->mMaterialIndex > 0)
    {
        auto aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];

        auto material = make_shared<Material>();
        material->mAmbient   = LoadMaterialTexture(aiMaterial, aiTextureType_AMBIENT);
        material->mDiffuse   = LoadMaterialTexture(aiMaterial, aiTextureType_DIFFUSE);
        material->mEmissive  = LoadMaterialTexture(aiMaterial, aiTextureType_EMISSIVE);
        material->mShininess = LoadMaterialTexture(aiMaterial, aiTextureType_SHININESS);
        material->mSpecular  = LoadMaterialTexture(aiMaterial, aiTextureType_SPECULAR);

        return material;
    }

    return nullptr;
}

VertexFormatSharedPtr
CreateModelVertexFormat()
{
    auto vertexFormat = make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

MeshSharedPtr
CreateMesh(
    _IN_     const aiScene *aiScene,
    _IN_     const aiMesh  *aiMesh)
{
    shared_ptr<Mesh> mesh;

    // Load vertex and index data.
    {
        auto vertexFormat = CreateModelVertexFormat();
        auto vertexGroup  = CreateModelVertexBuffer(aiMesh);
        auto indexBuffer  = CreateModelIndexBuffer(aiMesh);

        mesh = make_shared<Mesh>(vertexFormat, vertexGroup, indexBuffer);
    }

    // Load texture data in term of material.
    {
        mesh->SetMaterial(CreateMaterial(aiScene, aiMesh));
    }

    return mesh;
}

NodeSharedPtr
CreateNode(
    _IN_     const aiScene *aiScene,
    _IN_     const aiNode  *aiNode)
{
    auto node = make_shared<Node>();

    // Process each mesh located at the current node
    for (unsigned int i = 0; i < aiNode->mNumMeshes; ++i)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        node->AttachChild(CreateMesh(aiScene, aiScene->mMeshes[aiNode->mMeshes[i]]));
    }

    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (size_t i = 0; i < aiNode->mNumChildren; ++i)
    {
        node->AttachChild(CreateNode(aiScene, aiNode->mChildren[i]));
    }

    return node;
}

void
AssetImporter::ImportModel(Model *model, const std::string& modelFilePath)
{
    // Load model using Assimp
    static Assimp::Importer sAiModelImporter;
    auto aiScene = sAiModelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!aiScene || aiScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
        FALCON_ENGINE_THROW_EXCEPTION(string("Error: ") + sAiModelImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary children nodes and textures.
    model->SetNode(CreateNode(aiScene, aiScene->mRootNode));
}

}
