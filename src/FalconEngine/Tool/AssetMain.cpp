#include <FalconEngine/Content/AssetTool.h>
#include <FalconEngine/Content/AssetProcessor.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>

using namespace std;
using namespace FalconEngine;

int
main()
{
#if 1
    // Fonts
    AssetProcessor::BakeFont("Content/Font/LuciadaConsoleDistanceField.fnt");
    AssetProcessor::BakeFont("Content/Font/NSimSunDistanceField.fnt");

    // Models
    AssetProcessor::BakeModel("Content/Model/Engine/Axe.dae");
    AssetProcessor::BakeModel("Content/Model/Engine/Box.dae");
    AssetProcessor::BakeModel("Content/Model/Bedroom.dae");

    // Texture
    AssetProcessor::BakeTexture1d("Content/Texture/Engine/Gradiant 1d.png");
#endif

#if 0
    // Shader
    AssetTool assetTool;
    assetTool.D3DSetShaderCompiler("C:/Program Files (x86)/Windows Kits/10/bin/10.0.15063.0/x64/fxc.exe");
    assetTool.D3DBakeShader("Content/Shader/Font.vert.hlsl");
    assetTool.D3DBakeShader("Content/Shader/Font.frag.hlsl");
#endif

    return 0;
}