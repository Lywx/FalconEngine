#include <FalconEngine/Content/ModelImporter.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

namespace FalconEngine
{

bool
ModelImporter::Import(Model *model, const string& modelFilePath, const ModelImportOption& modelImportOption)
{
    // http://assimp.sourceforge.net/lib_html/
    const vector<string> modelExtensionSupportedList =
    {
        ".dae", // Collada
        ".xml",
        ".blend", // Blender
        ".bvh", // Biovision BVH
        ".3ds", // 3D Studio Max 3DS
        ".ase", // 3D Studio Max ASE
        ".obj", // Wavefront Object
        ".ply", // Stanford Polygon Library
        ".dxf", // AutoCAD DXF
        ".ifc", // IFC - STEP, Industry Foundation Classes
        ".nff", // Neutral File Format
        ".nff", // Sense8 WorldToolkit
        ".smd", // Valve Model
        ".vta",
        ".mdl", // Quake I
        ".md2", // Quake II
        ".md3", // Quake III
        ".pk3", // Quake 3 BSP 1
        ".mdc", // RtCW
        ".md5mesh", // Doom 3
        ".md5anim",
        ".md5camera",
        ".x", // DirectX X
        ".q3o", // Quick3D
        ".q3s",
        ".raw" // Raw Triangles
        ".ac", // AC3D.
        ".stl", // Stereolithography.
        ".dxf", // Autodesk DXF.
        ".irrmesh", // Irrlicht Mesh
        ".xml",
        ".irr" // Irrlicht Scene
        ".xml",
        ".off", // Object File Format.
        ".ter", // Terragen Terrain
        ".mdl", // 3D GameStudio Model
        ".hmp", // 3D GameStudio Terrain
        ".xml" // Ogre (*.mesh.xml, *.skeleton.xml, *.material)
        ".ms3d", // Milkshape 3D
        ".lwo", // LightWave Model
        ".lws", // LightWave Scene
        ".lxo", // Modo Model
        ".csm", // CharacterStudio Motion
        ".ply", // Stanford Ply
        ".cob", // TrueSpace
        ".scn",
        ".xgl", // XGL
        ".zgl",
    };

    auto modelFileExtension = GetFileExtension(modelFilePath);
    if (!IsFileExtensionSupported(modelFileExtension, modelExtensionSupportedList))
    {
        return false;
    }

    // Load model using Assimp.
    static Assimp::Importer sImporter;
    auto scene = sImporter.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (scene == nullptr
            || scene->mRootNode == nullptr
            || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(string("Error: ") + sImporter.GetErrorString());
    }

    // NOTE(Wuxiang): The node constructor would recursively load the necessary
    // children nodes and textures.
    model->SetNode(CreateNode(model, modelFilePath, modelImportOption, scene, scene->mRootNode));

    return true;
}

/************************************************************************/
/* Private Members                                                      */
/************************************************************************/
std::shared_ptr<Node>
ModelImporter::CreateNode(Model *model, const string& modelFilePath, const ModelImportOption& modelImportOption, const aiScene *aiScene, const aiNode *aiNode)
{
    auto node = make_shared<Node>();

    // Load node transform.
    node->mLocalTransform = Matrix4f(
                                aiNode->mTransformation[0][0], aiNode->mTransformation[1][0], aiNode->mTransformation[2][0], aiNode->mTransformation[3][0],  // Col 0
                                aiNode->mTransformation[0][1], aiNode->mTransformation[1][1], aiNode->mTransformation[2][1], aiNode->mTransformation[3][1],  // Col 1
                                aiNode->mTransformation[0][2], aiNode->mTransformation[1][2], aiNode->mTransformation[2][2], aiNode->mTransformation[3][2],  // Col 2
                                aiNode->mTransformation[0][3], aiNode->mTransformation[1][3], aiNode->mTransformation[2][3], aiNode->mTransformation[3][3]); // Col 3

    // Process each mesh located at the current node
    for (unsigned int i = 0; i < aiNode->mNumMeshes; ++i)
    {
        // The node object only contains indices to index the actual objects in the scene.
        // The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        node->AttachChild(CreateVisual(model, modelFilePath, modelImportOption, aiScene, aiScene->mMeshes[aiNode->mMeshes[i]]));
    }

    // After we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (size_t i = 0; i < aiNode->mNumChildren; ++i)
    {
        node->AttachChild(CreateNode(model, modelFilePath, modelImportOption, aiScene, aiNode->mChildren[i]));
    }

    return node;
}

std::shared_ptr<Mesh>
ModelImporter::CreateMesh(Model *model, const string& modelFilePath, const ModelImportOption& modelImportOption, const aiScene *aiScene, const aiMesh *aiMesh)
{
    // Load vertex and index data.
    auto vertexGroup = CreateVertexGroup(
                           model,
                           modelImportOption.mVertexBufferUsage,
                           modelImportOption.mVertexBufferLayout, aiMesh);
    auto indexBuffer = CreateIndexBuffer(
                           model,
                           modelImportOption.mIndexType,
                           modelImportOption.mIndexBufferUsage, aiMesh);

    auto primitive = make_shared<PrimitiveTriangles>(GetVertexFormat(), vertexGroup, indexBuffer);

    // Extract bounding box from mesh.
    primitive->SetAABB(CreateAABB(aiMesh));

    // Load texture data in term of material.
    auto material = CreateMaterial(modelFilePath, aiScene, aiMesh);

    return make_shared<Mesh>(primitive, material);
}

std::shared_ptr<Visual>
ModelImporter::CreateVisual(Model *model, const string& modelFilePath, const ModelImportOption& modelImportOption, const aiScene *aiScene, const aiMesh *aiMesh)
{
    // Create visual without vertex format and vertex group.
    return make_shared<Visual>(CreateMesh(model, modelFilePath, modelImportOption, aiScene, aiMesh));
}

AABB
ModelImporter::CreateAABB(const aiMesh *aiMesh)
{
    if (!aiMesh->mVertices)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Model doesn't have vertex data.");
    }

    auto aabb = AABB(Vector3f(aiMesh->mVertices[0].x,
                              aiMesh->mVertices[0].y,
                              aiMesh->mVertices[0].z));

    for (size_t vertexIndex = 1; vertexIndex < aiMesh->mNumVertices; ++vertexIndex)
    {
        aabb.Extend(Vector3f(aiMesh->mVertices[vertexIndex].x,
                             aiMesh->mVertices[vertexIndex].y,
                             aiMesh->mVertices[vertexIndex].z));
    }

    return aabb;
}

std::shared_ptr<IndexBuffer>
ModelImporter::CreateIndexBuffer(Model *model, IndexType indexType, BufferUsage indexBufferUsage, const aiMesh *aiMesh)
{
    switch (indexType)
    {
    case IndexType::UnsignedShort:
        return CreateIndexBufferInternal<unsigned short>(model, indexType, indexBufferUsage, aiMesh);

    case IndexType::UnsignedInt:
        return CreateIndexBufferInternal<unsigned int>(model, indexType, indexBufferUsage, aiMesh);

    default:
        FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
    }
}

std::shared_ptr<VertexFormat>
ModelImporter::CreateVertexFormat()
{
    auto vertexFormat = std::make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 1);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 2);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

std::shared_ptr<VertexFormat>
ModelImporter::GetVertexFormat()
{
    static auto vertexFormat = CreateVertexFormat();
    return vertexFormat;
}

std::shared_ptr<VertexGroup>
ModelImporter::CreateVertexGroup(
    _IN_OUT_ Model                      *model,
    _IN_     const ModelUsageOption&     vertexBufferUsage,
    _IN_     const ModelLayoutOption& /* vertexBufferLayout */,
    _IN_     const aiMesh               *aiMesh)
{
    static auto sMasterRenderer = Renderer::GetInstance();

    // NOTE(Wuxiang): I think interleaving is not ideal for model loading. Because
    // the interleaving combines with indexed rendering doesn't get all the benefit
    // of locality of data in the memory. At the cost of flexibility, interleaving
    // doesn't provide much flexibility in this case from my understanding.

    // Memory allocation for vertex buffer.
    auto vertexNum = int(aiMesh->mNumVertices);

    // Position
    auto vertexBuffer = std::make_shared<VertexBuffer>(
                            vertexNum, sizeof(ModelVertex::mPosition),
                            BufferStorageMode::Device,
                            vertexBufferUsage.mPosition);
    {
        auto vertexData = reinterpret_cast<Vector3f *>(
                              sMasterRenderer->Map(
                                  vertexBuffer.get(),
                                  BufferAccessMode::WriteBuffer,
                                  BufferFlushMode::Automatic,
                                  BufferSynchronizationMode::Unsynchronized,
                                  vertexBuffer->GetDataOffset(),
                                  vertexBuffer->GetDataSize()));

        for (size_t vertexIndex = 0;
                vertexIndex < aiMesh->mNumVertices;
                ++vertexIndex)
        {
            vertexData[vertexIndex] = Vector3f(aiMesh->mVertices[vertexIndex].x,
                                               aiMesh->mVertices[vertexIndex].y,
                                               aiMesh->mVertices[vertexIndex].z);
        }

        sMasterRenderer->Unmap(vertexBuffer.get());
    }

    // Normal
    auto normalBuffer = std::make_shared<VertexBuffer>(vertexNum,
                        sizeof(ModelVertex::mNormal), BufferStorageMode::Device, vertexBufferUsage.mNormal);
    {
        auto normalData = reinterpret_cast<Vector3f *>(
                              sMasterRenderer->Map(
                                  normalBuffer.get(),
                                  BufferAccessMode::WriteBuffer,
                                  BufferFlushMode::Automatic,
                                  BufferSynchronizationMode::Unsynchronized,
                                  normalBuffer->GetDataOffset(),
                                  normalBuffer->GetDataSize()));

        for (size_t vertexIndex = 0; vertexIndex < aiMesh->mNumVertices; ++vertexIndex)
        {
            if (aiMesh->mNormals)
            {
                normalData[vertexIndex] = Vector3f(aiMesh->mNormals[vertexIndex].x,
                                                   aiMesh->mNormals[vertexIndex].y,
                                                   aiMesh->mNormals[vertexIndex].z);
            }
            else
            {
                // NOTE(Wuxiang): It is allowed to have no normal. If it is
                // the case, fill them as zero.
                normalData[vertexIndex] = Vector3f::Zero;
            }
        }

        sMasterRenderer->Unmap(normalBuffer.get());
    }

    // Texture coordinate
    auto texCoordBuffer = std::make_shared<VertexBuffer>(vertexNum,
                          sizeof(ModelVertex::mTexCoord), BufferStorageMode::Device, vertexBufferUsage.mTexCoord);
    {
        auto texCoordData = reinterpret_cast<Vector2f *>(
                                sMasterRenderer->Map(
                                    texCoordBuffer.get(),
                                    BufferAccessMode::WriteBuffer,
                                    BufferFlushMode::Automatic,
                                    BufferSynchronizationMode::Unsynchronized,
                                    texCoordBuffer->GetDataOffset(),
                                    texCoordBuffer->GetDataSize()));

        for (size_t vertexIndex = 0; vertexIndex < aiMesh->mNumVertices; ++vertexIndex)
        {
            if (aiMesh->mTextureCoords[0])
            {
                // NOTE(Wuxiang): A vertex can contain up to 8 different texture
                // coordinates.
                texCoordData[vertexIndex] = Vector2f(aiMesh->mTextureCoords[0][vertexIndex].x,
                                                     aiMesh->mTextureCoords[0][vertexIndex].y);
            }
            else
            {
                // NOTE(Wuxiang): It is allowed to have no texture coordinate. If it is
                // the case, fill them as zero.
                texCoordData[vertexIndex] = Vector2f::Zero;
            }
        }

        sMasterRenderer->Unmap(texCoordBuffer.get());
    }

    model->mVertexNum += vertexNum;

    auto vertexFormat = GetVertexFormat();
    auto vertexGroup = make_shared<VertexGroup>();
    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
    vertexGroup->SetVertexBuffer(1, normalBuffer, 0, vertexFormat->GetVertexBufferStride(1));
    vertexGroup->SetVertexBuffer(2, texCoordBuffer, 0, vertexFormat->GetVertexBufferStride(2));
    return vertexGroup;
}

std::shared_ptr<Material>
ModelImporter::CreateMaterial(const string& modelFilePath, const aiScene *aiScene, const aiMesh *aiMesh)
{
    auto material = make_shared<Material>();

    auto aiMaterial = aiScene->mMaterials[aiMesh->mMaterialIndex];

    // @ref http://assimp.sourceforge.net/lib_html/materials.html
    material->mAmbientColor = GetMaterialColor(aiMaterial, AI_MATKEY_COLOR_AMBIENT);
    material->mDiffuseColor = GetMaterialColor(aiMaterial, AI_MATKEY_COLOR_DIFFUSE);
    material->mEmissiveColor = GetMaterialColor(aiMaterial, AI_MATKEY_COLOR_EMISSIVE);
    material->mShininess = GetMaterialFloat(aiMaterial, AI_MATKEY_SHININESS);
    material->mSpecularColor = GetMaterialColor(aiMaterial, AI_MATKEY_COLOR_SPECULAR);

    auto modelDirectoryPath = GetFileDirectory(modelFilePath);
    material->mAmbientTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_AMBIENT);
    material->mDiffuseTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_DIFFUSE);
    material->mEmissiveTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_EMISSIVE);
    material->mShininessTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_SHININESS);
    material->mSpecularTexture = LoadMaterialTexture(modelDirectoryPath, aiMaterial, aiTextureType_SPECULAR);

    return material;
}

Color
ModelImporter::GetMaterialColor(aiMaterial *aiMaterial, const char *param1, int param2, int param3)
{
    aiColor3D color(0.f, 0.f, 0.f);

    if (AI_SUCCESS != aiMaterial->Get(param1, param2, param3, color))
    {
        return ColorPalette::Transparent;
    }

    return Color(color.r, color.g, color.b);
}

float
ModelImporter::GetMaterialFloat(aiMaterial *aiMaterial, const char *param1, int param2, int param3)
{
    float constant;
    if (AI_SUCCESS != aiMaterial->Get(param1, param2, param3, constant))
    {
        return 0.0f;
    }

    return constant;
}

Texture2d *
ModelImporter::LoadMaterialTexture(const string& modelDirectoryPath, const aiMaterial *material, aiTextureType materialType)
{
    // NOTE(Wuxiang): I think most material only has one texture for each texture type.
    auto textureNum = material->GetTextureCount(materialType);
    if (textureNum > 0)
    {
        auto assetManager = AssetManager::GetInstance();

        // NOTE(Wuxiang): Since currently we only support one material per type,
        // we return immediately after get the texture at index 0.
        // Read texture file path.
        aiString textureFilePath;
        material->GetTexture(materialType, 0, &textureFilePath);

        // NOTE(Wuxiang): Get texture from asset manager without duplication using asset
        // manager's duplication checking mechanics.

        // NOTE(Wuxiang): Add .bin to file path so that the texture file is
        // loaded from preprocessed asset file.
        auto texture = assetManager->LoadTexture<Texture2d>(modelDirectoryPath + AddAssetExtension(textureFilePath.C_Str()));
        return texture.get();
    }

    return nullptr;
}

}
