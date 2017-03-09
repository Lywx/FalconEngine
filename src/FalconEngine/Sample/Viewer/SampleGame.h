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
    HandednessRight mHandedness;

    // Camera
    FirstPersonCameraSharedPtr mCamera;

    // Fonts
    const BitmapFont *mFont_Console = nullptr;
    const BitmapFont *mFont_Chinese = nullptr;

    // Scene
    NodeSharedPtr mSceneNode;

    PhongLightingEffectSharedPtr mSceneLightingEffect;
    std::shared_ptr<Light> mDirectionalLight;
    std::shared_ptr<Light> mPointLight1;
    std::shared_ptr<Light> mPointLight2;

    std::vector<const Light *> mScenePointLightList;
    std::vector<const Light *> mSceneSpotLightList;

    // Entities
    // std::shared_ptrEntity> mCharacter;
    // std::shared_ptr<LightEntity> mLamp1;
    // std::shared_ptr<LightEntity> mLamp2;
    std::shared_ptr<SceneEntity> mRoom;
};

}
