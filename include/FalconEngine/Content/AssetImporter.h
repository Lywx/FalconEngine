#pragma once

#include <FalconEngine/Content/ContentInclude.h>

namespace FalconEngine
{

class Model;

class AssetImporter
{
public:
    static void
    ImportModel(
        _IN_OUT_ Model             *model,
        _IN_     const std::string& modelFilePath);
};

}
