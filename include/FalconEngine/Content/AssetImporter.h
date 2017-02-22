#pragma once

#include <FalconEngine/Content/ContentInclude.h>
#include <FalconEngine/Graphics/Renderers/VisualEffectInstance.h>

namespace FalconEngine
{

class Model;
class VisualEffect;
class AssetImporter
{
public:
    static void
    ImportModel(Model *model, const std::string& modelFilePath, const VisualEffectInstanceSharedPtr effectInstance);
};

}
