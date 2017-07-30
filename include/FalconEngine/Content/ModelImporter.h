#pragma once

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <FalconEngine/Content/AssetManager.h>
#include <FalconEngine/Core/Path.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveTriangles.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
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
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Math/AABB.h>

using namespace std;

namespace FalconEngine
{

#pragma pack(push, 1)
class FALCON_ENGINE_API ModelVertex
{
public:
    Vector3f mPosition;
    Vector3f mNormal;
    Vector2f mTexCoord;
};
#pragma pack(pop)

class ModelImporter
{
public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static bool
    Import(Model *model, const string& modelFilePath, const ModelImportOption& modelImportOption);

private:
    /************************************************************************/
    /* Private Members                                                      */
    /************************************************************************/
    // @remark model directory path is necessary for loading texture accompanying
    // the model files.
    static std::shared_ptr<Node>
    CreateNode(_IN_OUT_ Model                   *model,
               _IN_     const string&            modelFilePath,
               _IN_     const ModelImportOption& modelImportOption,
               _IN_     const aiScene           *aiScene,
               _IN_     const aiNode            *aiNode);

    static std::shared_ptr<Mesh>
    CreateMesh(_IN_OUT_ Model                   *model,
               _IN_     const string&            modelFilePath,
               _IN_     const ModelImportOption& modelImportOption,
               _IN_     const aiScene           *aiScene,
               _IN_     const aiMesh            *aiMesh);

    static std::shared_ptr<Visual>
    CreateVisual(_IN_OUT_ Model                   *model,
                 _IN_     const string&            modelFilePath,
                 _IN_     const ModelImportOption& modelImportOption,
                 _IN_     const aiScene           *aiScene,
                 _IN_     const aiMesh            *aiMesh);

    // NEW(Wuxiang): Bounding box loading has a lot of space for optimization.
    // You could precomputed the bounding box in the asset processor.
    static AABB
    CreateAABB(const aiMesh *aiMesh);

    static std::shared_ptr<IndexBuffer>
    CreateIndexBuffer(_IN_OUT_ Model        *model,
                      _IN_     IndexType     indexType,
                      _IN_     BufferUsage   indexBufferUsage,
                      _IN_     const aiMesh *aiMesh);

    template <typename T>
    static std::shared_ptr<IndexBuffer>
    CreateIndexBufferInternal(_IN_OUT_ Model        *model,
                              _IN_     IndexType     indexType,
                              _IN_     BufferUsage   indexBufferUsage,
                              _IN_     const aiMesh *aiMesh)
    {
        // Sum space for the index buffer memory allocation.
        int indexNum = 0;
        {
            for (unsigned int faceIndex = 0; faceIndex < aiMesh->mNumFaces; ++faceIndex)
            {
                indexNum += aiMesh->mFaces[faceIndex].mNumIndices;
            }
        }

        static auto sMasterRenderer = Renderer::GetInstance();

        // Memory allocation for index buffer.
        auto indexBuffer = std::make_shared<IndexBuffer>(indexNum, indexType,
                           BufferStorageMode::Device, indexBufferUsage);
        {
            auto indexData = reinterpret_cast<T *>(
                                 sMasterRenderer->Map(
                                     indexBuffer.get(),
                                     BufferAccessMode::WriteBuffer,
                                     BufferFlushMode::Automatic,
                                     BufferSynchronizationMode::Unsynchronized,
                                     indexBuffer->GetDataOffset(),
                                     indexBuffer->GetDataSize()));
            // Walk through each of the mesh's faces (a face is a mesh its triangle)
            // and retrieve the corresponding vertex indexes.
            int indexNumAdded = 0;
            for (unsigned int faceIndex = 0; faceIndex < aiMesh->mNumFaces; ++faceIndex)
            {
                auto& face = aiMesh->mFaces[faceIndex];
                for (unsigned int i = 0; i < face.mNumIndices; ++i)
                {
                    indexData[indexNumAdded] = T(face.mIndices[i]);
                    ++indexNumAdded;
                }
            }

            sMasterRenderer->Unmap(indexBuffer.get());
        }

        // Update model metadata.
        model->mIndexNum += indexNum;

        return indexBuffer;
    }

    static std::shared_ptr<VertexFormat>
    CreateVertexFormat();

    static std::shared_ptr<VertexFormat>
    GetVertexFormat();

    // @remark In any case, the vertex buffer contains interlaced data of vertex
    // position, normal and texture coordinate.
    static std::shared_ptr<VertexGroup>
    CreateVertexGroup(_IN_OUT_ Model                   *model,
                      _IN_     const ModelUsageOption&  vertexBufferUsage,
                      _IN_     const ModelLayoutOption& vertexBufferLayout,
                      _IN_     const aiMesh            *aiMesh);

    static std::shared_ptr<Material>
    CreateMaterial(
        _IN_ const string&  modelFilePath,
        _IN_ const aiScene *aiScene,
        _IN_ const aiMesh  *aiMesh);

    static Color
    GetMaterialColor(aiMaterial *aiMaterial, const char *param1, int param2, int param3);

    static float
    GetMaterialFloat(aiMaterial *aiMaterial, const char *param1, int param2, int param3);

    static Texture2d *
    LoadMaterialTexture(_IN_ const string&     modelDirectoryPath,
                        _IN_ const aiMaterial *material,
                        _IN_ aiTextureType     materialType);
};

}
