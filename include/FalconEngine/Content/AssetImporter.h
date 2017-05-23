#pragma once

#include <FalconEngine/Content/Header.h>

namespace FalconEngine
{

class Mesh;
class Model;

class FALCON_ENGINE_API AssetImporter
{
public:
    static void
    Import(
        _IN_OUT_ Model             *model,
        _IN_     const std::string& modelFilePath);
};

}
