#pragma once

#include <FalconEngine/Content.h>
#include <FalconEngine/Context.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Input.h>
#include <FalconEngine/Math.h>

#include <FalconEngine/Graphics/Effect/PhongShadingEffect.h>

namespace FalconEngine
{

class SampleGame : public Game
{
public:
    SampleGame();
    ~SampleGame();

public:
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
    const Font *mFont = nullptr;

    // Scene
    std::shared_ptr<SceneEntity>        mScene;
    std::shared_ptr<PhongShadingEffect> mSceneLightingEffect;
    std::shared_ptr<Light>              mSceneDirectionalLight;
    std::vector<const Light *>          mScenePointLightList;
    std::vector<const Light *>          mSceneSpotLightList;

    // Entities
    std::shared_ptr<PointLightEntity> mPointLight1;
    std::shared_ptr<PointLightEntity> mPointLight2;
    std::shared_ptr<PointLightEntity> mPointLight3;
};

}
