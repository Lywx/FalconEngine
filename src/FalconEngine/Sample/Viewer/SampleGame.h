#pragma once

#include <FalconEngine/Content.h>
#include <FalconEngine/Context.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Input.h>
#include <FalconEngine/Math.h>

namespace FalconEngine
{

class SampleGame : public Game
{
public:
    SampleGame();
    ~SampleGame();

public:
    virtual GameEngineSettingsSharedPtr
    GetEngineSettings() override;

    virtual void
    Initialize() override;

    virtual void
    Render(GameEngineGraphics *graphics, double percent) override;

    virtual void
    Update(GameEngineInput *input, double elapsed) override;

private:
    AssetManager *mAssetManager = nullptr;

    // Camera
    FirstPersonCameraSharedPtr mCamera;

    // Fonts
    const BitmapFont *mFontConsole = nullptr;
    const BitmapFont *mFontDisplay = nullptr;

    HandednessRight mHandedness;

    // Scene
    NodeSharedPtr mScene;
    PhongLightingEffectSharedPtr mSceneLightingEffect;

    LightSharedPtr mSceneDirectionalLight;
    std::vector<const Light *> mScenePointLightList;
    std::vector<const Light *> mSceneSpotLightList;

    // Entities
    EntitySharedPtr mCharacter;

    std::shared_ptr<LightEntity> mLamp1;
    std::shared_ptr<LightEntity> mLamp2;
};

}
