#pragma once

#include <FalconEngine/Content.h>
#include <FalconEngine/Context.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Input.h>
#include <FalconEngine/Math.h>
#include <FalconEngine/Graphics/Effect/PhongEffect.h>

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
    ThirdPersonCameraSharedPtr mCamera;

    // Fonts
    const Font *mFont = nullptr;

    // Scene
    std::shared_ptr<SceneEntity>       mScene;
    std::shared_ptr<PhongEffect>       mSceneLightingEffect;
    std::shared_ptr<PhongEffectParams> mSceneLightingParams;

    // Entities
    std::shared_ptr<LightEntity> mDirectionalLight;
    std::shared_ptr<LightEntity> mPointLight1;
    std::shared_ptr<LightEntity> mPointLight2;
    std::shared_ptr<LightEntity> mPointLight3;

    // Nodes
    std::shared_ptr<Node> mAxeNode;
    std::shared_ptr<Node> mRoomNode;
};

}
