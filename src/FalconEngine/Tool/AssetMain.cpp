#include <FalconEngine/Content/AssetTool.h>
#include <FalconEngine/Content/AssetProcessor.h>
#include <FalconEngine/Platform/OpenGL/OpenGLShader.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>

using namespace std;
using namespace FalconEngine;

void
BakeAssets()
{
    auto assetProcessor = AssetProcessor();

    // Fonts
    assetProcessor.BakeFont("Content/Font/LuciadaConsoleDistanceField.fnt");
    assetProcessor.BakeFont("Content/Font/NSimSunDistanceField.fnt");

    // Models
    assetProcessor.BakeModel("Content/Model/Engine/Axe.dae");
    assetProcessor.BakeModel("Content/Model/Engine/Box.dae");
    assetProcessor.BakeModel("Content/Model/Bedroom.dae");

    // Texture
    assetProcessor.BakeTexture1d("Content/Texture/Engine/Gradiant 1d.png");
}

int
main()
{
    AssetTool::Initialize();

    BakeAssets();

    return 0;
}