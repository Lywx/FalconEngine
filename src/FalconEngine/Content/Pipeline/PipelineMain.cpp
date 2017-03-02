#include <FalconEngine/ContentInclude.h>
#include <FalconEngine/Content/AssetProcessor.h>

using namespace std;
using namespace FalconEngine;

int
main(int argc, char **argv)
{
    auto assetProcessor = AssetProcessor();

    // Fonts
    // assetProcessor.BakeFont("Content/Fonts/LuciadaConsoleDistanceField.fnt");
    // assetProcessor.BakeFont("Content/Fonts/NSimSunDistanceField.fnt");

    // Models
    // assetProcessor.BakeModel("Content/Models/Axe.obj");
    // assetProcessor.BakeModel("Content/Models/Carl.stl");
    assetProcessor.BakeModel("Content/Models/nanosuit.obj");

    return 0;
}

