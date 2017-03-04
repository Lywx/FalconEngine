#pragma once

#include <FalconEngine/ContentInclude.h>

namespace FalconEngine
{

class Mesh;
using MeshSharedPtr = std::shared_ptr<Mesh>;

class Model;

class AssetImporter
{
public:
    static void
    Import(
        _IN_OUT_ Model             *model,
        _IN_     const std::string& modelFilePath);
};

}
