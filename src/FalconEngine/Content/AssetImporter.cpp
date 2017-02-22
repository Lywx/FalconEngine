#include <FalconEngine/Content/AssetImporter.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Graphics/Scenes/Mesh.h>
#include <FalconEngine/Graphics/Scenes/Model.h>
#include <FalconEngine/Graphics/Scenes/Node.h>

using namespace std;

namespace FalconEngine
{

VertexGroupSharedPtr
CreateModelVertexBuffer(const aiMesh *mesh)
{
    // Memory allocation for vertex buffer.
    auto vertexNum = mesh->mNumVertices;
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
    auto indexes = reinterpret_cast<ModelIndex *>(indexBuffer->mData);

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

// ReSharper disable once CppNotAllPathsReturnValue
int
GetTextureUnitFrom(aiTextureType textureType)
{
    switch (textureType)
    {
    case aiTextureType_NONE:
        break;
    case aiTextureType_DIFFUSE:
        return GetTextureUnit(TextureUnit::Diffuse);
    case aiTextureType_SPECULAR:
        return GetTextureUnit(TextureUnit::Specular);
    case aiTextureType_AMBIENT:
        return GetTextureUnit(TextureUnit::Ambient);
    case aiTextureType_EMISSIVE:
        break;
    case aiTextureType_HEIGHT:
        break;
    case aiTextureType_NORMALS:
        break;
    case aiTextureType_SHININESS:
        break;
    case aiTextureType_OPACITY:
        break;
    case aiTextureType_DISPLACEMENT:
        break;
    case aiTextureType_LIGHTMAP:
        break;
    case aiTextureType_REFLECTION:
        break;
    case aiTextureType_UNKNOWN:
        break;
    case _aiTextureType_Force32Bit:
        break;
    default:
        FALCON_ENGINE_NOT_POSSIBLE();
    }

    FALCON_ENGINE_NOT_SUPPORT();
}

void
LoadMaterialTexture(
    _IN_OUT_ Mesh             *mesh,
    _IN_     const aiMaterial *material,
    _IN_     aiTextureType     textureType)
{
    int textureNum = material->GetTextureCount(textureType);
    if (textureNum > 0)
    {
        auto assetManager = AssetManager::GetInstance();
        auto effectInstance = mesh->GetEffectInstance();

        // Walk through every piece of material and load texture if needed
        for (int textureIndex = 0; textureIndex < textureNum; ++textureIndex)
        {
            // Read texture file path.
            aiString textureFilePath;
            material->GetTexture(textureType, textureIndex, &textureFilePath);

            // Get texture from asset manager without duplication using asset
            // manager's duplication checking mechanics.
            auto texture = assetManager->LoadTexture2d(textureFilePath.C_Str());
            effectInstance->SetShaderTexture(0, GetTextureUnitFrom(textureType), texture);
        }
    }
}


// @param model - the model owns this mesh.
// @param material - the material to load from.
// @param materialTextureIndexVector - index of material's texture into the model's texture vector.
// @param materialTextureType - the texture type to load from.
void
CreateMeshTexture(
    _IN_OUT_  Mesh          *mesh,
    _OUT_     const aiScene *aiScene,
    _OUT_     const aiMesh  *aiMesh)
{
    // Walk through each of the material and retrieve the corresponding textures.
    if (aiMesh->mMaterialIndex >= 0)
    {
        auto material = aiScene->mMaterials[aiMesh->mMaterialIndex];

        LoadMaterialTexture(mesh, material, aiTextureType_AMBIENT);
        LoadMaterialTexture(mesh, material, aiTextureType_DIFFUSE);
        LoadMaterialTexture(mesh, material, aiTextureType_SPECULAR);
    }
}
VertexFormatSharedPtr
CreateModelVertexFormat()
{
    auto vertexFormat = make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "mPosition", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "mNormal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "mTexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

MeshSharedPtr
CreateMesh(
    _IN_     const VisualEffectInstanceSharedPtr effectInstance,
    _IN_     const aiScene                      *aiScene,
    _IN_     const aiMesh                       *aiMesh)
{
    shared_ptr<Mesh> mesh;

    // Load vertex and index data.
    {
        auto vertexFormat = CreateModelVertexFormat();
        auto vertexGroup = CreateModelVertexBuffer(aiMesh);
        auto indexBuffer = CreateModelIndexBuffer(aiMesh);

        mesh = make_shared<Mesh>(vertexFormat, vertexGroup, indexBuffer);
    }

    // Load texture data.
    {
        // NOTE(Wuxiang): It is important for mesh having a effect instance so that
        // the model importer would be able to set the texture and sampler in the
        // effect instance.
        mesh->SetEffectInstance(effectInstance);

        CreateMeshTexture(mesh.get(), aiScene, aiMesh);
    }

    return mesh;
}

NodeSharedPtr
CreateNode(
    _IN_     const VisualEffectInstanceSharedPtr effectInstance,
    _IN_     const aiScene                      *aiScene,
    _IN_     const aiNode                       *aiNode)
{
    auto node = make_shared<Node>();

    // Process each mesh located at the current node
    for (unsigned int i = 0; i < aiNode->mNumMeshes; ++i)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        node->AttachChild(CreateMesh(effectInstance, aiScene, aiScene->mMeshes[aiNode->mMeshes[i]]));
    }

    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (size_t i = 0; i < aiNode->mNumChildren; ++i)
    {
        node->AttachChild(CreateNode(effectInstance, aiScene, aiNode->mChildren[i]));
    }

    return node;
}

void
AssetImporter::ImportModel(Model *model, const std::string& modelFilePath, const VisualEffectInstanceSharedPtr effectInstance)
{
    // Load model using Assimp
    static Assimp::Importer aiModelImporter;
    auto aiScene = aiModelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!aiScene || aiScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
        ThrowRuntimeException(string("Error: ") + aiModelImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary children nodes and textures.
    model->SetNode(CreateNode(effectInstance, aiScene, aiScene->mRootNode));
}

}
