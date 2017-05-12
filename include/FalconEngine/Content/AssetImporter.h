#pragma once

#include <FalconEngine/Content/Header.h>

namespace FalconEngine
{

class Mesh;
using MeshSharedPtr = std::shared_ptr<Mesh>;

class Model;

class FALCON_ENGINE_ITEM_CONTENT AssetImporter
{
public:
    static void
    Import(
        _IN_OUT_ Model             *model,
        _IN_     const std::string& modelFilePath);
};

}
