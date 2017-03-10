#include <FalconEngine/Content/AssetImporter.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Content/Path.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Resource/Buffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/IndexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Scene/Material.h>
#include <FalconEngine/Graphics/Renderer/Scene/Mesh.h>
#include <FalconEngine/Graphics/Renderer/Scene/Model.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Math/Bound/AABBBoundingBox.h>

using namespace std;

namespace FalconEngine
{

using AABBBoundingBoxSharedPtr = shared_ptr<AABBBoundingBox>;

AABBBoundingBoxSharedPtr
CreateMeshAABBBoundingBox(const aiMesh *aiMesh)
{
    if (!aiMesh->mVertices)
    {
        FALCON_ENGINE_THROW_EXCEPTION("Model doesn't have vertex data.");
    }

    auto boundingBox = make_shared<AABBBoundingBox>(Vector3f(aiMesh->mVertices[0].x,
                       aiMesh->mVertices[0].y,
                       aiMesh->mVertices[0].z));

    for (size_t i = 0; i < aiMesh->mNumVertices; ++i)
    {
        boundingBox->UpdatePosition(Vector3f(aiMesh->mVertices[i].x,
                                             aiMesh->mVertices[i].y,
                                             aiMesh->mVertices[i].z));
    }

    return boundingBox;
}

IndexBufferSharedPtr
CreateMeshIndexBuffer(const aiMesh *mesh)
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

VertexGroupSharedPtr
CreateMeshVertexGroup(const aiMesh *aiMesh)
{
    // Memory allocation for vertex buffer.
    auto vertexNum = int(aiMesh->mNumVertices);
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

        // Position
        vertex.mPosition = Vector3f(aiMesh->mVertices[i].x,
                                    aiMesh->mVertices[i].y,
                                    aiMesh->mVertices[i].z);

        // Normal
        vertex.mNormal = Vector3f(aiMesh->mNormals[i].x,
                                  aiMesh->mNormals[i].y,
                                  aiMesh->mNormals[i].z);

        // Texture coordinate
        if (aiMesh->mTextureCoords[0])
        {
            // NOTE(Wuxiang): A vertex can contain up to 8 different texture
            // coordinates.
            vertex.mTexCoord = Vector2f(aiMesh->mTextureCoords[0][i].x,
                                        aiMesh->mTextureCoords[0][i].y);
        }

        // NOTE(Wuxiang): It is allowed to have no texture coordinate.
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
    return vertexGroup;
}

Texture2d *
LoadMaterialTexture(
    _IN_ const string&     modelDirectoryPath,
    _IN_ const aiMaterial *material,
    _IN_ aiTextureType     materialType)
{
    // NOTE(Wuxiang): I think most material only has one texture for each texture type.
    auto textureNum = material->GetTextureCount(materialType);
    if (textureNum > 0)
    {
        auto assetManager = AssetManager::GetInstance();

        // Walk through every piece of material and load texture if needed

        // NOTE(Wuxiang): Since currently we only support one material per type,
        // we return immediately after get the texture at index 0.
        for (decltype(textureNum) textureIndex = 0; textureIndex < textureNum; ++textureIndex)
        {
            // Read texture file path.
            aiString textureFilePath;
            material->GetTexture(materialType, textureIndex, &textureFilePath);

            // Get texture from asset manager without duplication using asset
            // manager's duplication checking mechanics.

            // NOTE(Wuxiang): Add .bin to file path so that the texture file is
            // loaded from preprocessed asset file.
            auto texture = assetManager->LoadTexture(modelDirectoryPath + AddAssetExtension(textureFilePath.C_Str()));
            return texture.get();
        }
    }

    return nullptr;
}

Color
LoadMaterialColor(aiMaterial *aiMaterial, const char *param1, int param2, int param3)
{
    aiColor3D color(0.f, 0.f, 0.f);

    if (AI_SUCCESS != aiMaterial->Get(param1, param2, param3, color))
    {
        return ColorPalette::Transparent;
    }

    return Color(color.r, color.g, color.b);
}

float
LoadMaterialFloat(aiMaterial *aiMaterial, const char *param1, int param2, int param3)
{
    float constant;
    if (AI_SUCCESS != aiMaterial->Get(param1, param2, param3, constant))
    {
        return 0.0f;
    }

    return constant;

}

MaterialSharedPtr
CreateMaterial(
    _IN_ const string&  modelDirectoryPath,
    _IN_ const aiScene *aiScene,
    _IN_ const aiMesh  *aiMesh)
{
    // When material exists.
    auto material = make_shared<Material>();

    if (aiMesh->mMaterialIndex > 0)
    {
        auto aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];

        // @ref http://assimp.sourceforge.net/lib_html/materials.html
        material->mAmbientColor = LoadMaterialColor(aiMaterial, AI_MATKEY_COLOR_AMBIENT);
        material->mDiffuseColor = LoadMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE);
        material->mEmissiveColor = LoadMaterialColor(aiMaterial, AI_MATKEY_COLOR_EMISSIVE);
        material->mShininess = LoadMaterialFloat(aiMaterial, AI_MATKEY_SHININESS);
        material->mSpecularColor  = LoadMaterialColor(aiMaterial, AI_MATKEY_COLOR_SPECULAR);

        material->mAmbientTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_AMBIENT);
        material->mDiffuseTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_DIFFUSE);
        material->mEmissiveTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_EMISSIVE);
        material->mShininessTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_SHININESS);
        material->mSpecularTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_SPECULAR);
    }

    return material;
}

VertexFormatSharedPtr
CreateMeshVertexFormat()
{
    shared_ptr<VertexFormat> static sVertexFormat;
    if (sVertexFormat == nullptr)
    {
        sVertexFormat = make_shared<VertexFormat>();
        sVertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
        sVertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
        sVertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
        sVertexFormat->FinishVertexAttribute();
    }

    return sVertexFormat;
}

MeshSharedPtr
CreateMesh(
    _IN_ const string&  modelDirectoryPath,
    _IN_ const aiScene *aiScene,
    _IN_ const aiMesh  *aiMesh)
{
    // Load vertex and index data.
    auto boundingBox  = CreateMeshAABBBoundingBox(aiMesh);
    auto indexBuffer  = CreateMeshIndexBuffer(aiMesh);
    auto vertexFormat = CreateMeshVertexFormat();
    auto vertexGroup  = CreateMeshVertexGroup(aiMesh);

    auto primitives = make_shared<PrimitiveTriangles>(vertexFormat, vertexGroup, indexBuffer);
    primitives->SetBoundingBox(boundingBox);

    auto mesh = make_shared<Mesh>(primitives);

    // Load texture data in term of material.
    mesh->SetMaterial(CreateMaterial(modelDirectoryPath, aiScene, aiMesh));

    return mesh;
}

NodeSharedPtr
CreateNode(
    _IN_ const string&  modelDirectoryPath,
    _IN_ const aiScene *aiScene,
    _IN_ const aiNode  *aiNode)
{
    auto node = make_shared<Node>();

    // Load node transform.
    node->mLocalTransform = Matrix4f(
                                aiNode->mTransformation[0][0], aiNode->mTransformation[1][0], aiNode->mTransformation[2][0], aiNode->mTransformation[3][0],
                                aiNode->mTransformation[0][1], aiNode->mTransformation[1][1], aiNode->mTransformation[2][1], aiNode->mTransformation[3][1],
                                aiNode->mTransformation[0][2], aiNode->mTransformation[1][2], aiNode->mTransformation[2][2], aiNode->mTransformation[3][2],
                                aiNode->mTransformation[0][3], aiNode->mTransformation[1][3], aiNode->mTransformation[2][3], aiNode->mTransformation[3][3]);

    // Process each mesh located at the current node
    for (unsigned int i = 0; i < aiNode->mNumMeshes; ++i)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        node->AttachChild(CreateMesh(modelDirectoryPath, aiScene, aiScene->mMeshes[aiNode->mMeshes[i]]));
    }

    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (size_t i = 0; i < aiNode->mNumChildren; ++i)
    {
        node->AttachChild(CreateNode(modelDirectoryPath, aiScene, aiNode->mChildren[i]));
    }

    return node;
}

void
AssetImporter::Import(Model *model, const std::string& modelFilePath)
{
    // Load model using Assimp.
    static Assimp::Importer sAiModelImporter;
    auto aiScene = sAiModelImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!aiScene || aiScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aiScene->mRootNode)
    {
        FALCON_ENGINE_THROW_EXCEPTION(string("Error: ") + sAiModelImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary children nodes and textures.
    model->SetNode(CreateNode(GetFileDirectory(modelFilePath), aiScene, aiScene->mRootNode));
}

}
