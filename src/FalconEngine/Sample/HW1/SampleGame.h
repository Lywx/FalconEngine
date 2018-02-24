#pragma once

#include <FalconEngine/Content.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Core.h>
#include <FalconEngine/Graphics.h>
#include <FalconEngine/Input.h>
#include <FalconEngine/Math.h>

#include <FalconEngine/Graphics/Effect/PhongEffect.h>
#include "FalconEngine/Graphics/Effect/SkyEffect.h"

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
    UpdateFrame(GameEngineGraphics *graphics, GameEngineInput *input, double elasped) override;

    virtual void
    Update(GameEngineGraphics *graphics, GameEngineInput *input, double elapsed) override;

private:
    bool
    BadCollisionTest(const Node *node);

private:
    // Camera
    std::shared_ptr<FirstPersonCamera> mCamera;

    // Fonts
    const Font *mFont = nullptr;

    // Effects
    std::shared_ptr<PhongEffect> mSceneLightingEffect;
    std::shared_ptr<PhongEffectParams> mSceneLightingParams;
    std::shared_ptr<SkyEffect> mSceneSkyEffect;
    std::shared_ptr<SkyEffectParams> mSceneSkyParams;

    // Nodes
    std::shared_ptr<Node> mTerrainNode;
    std::shared_ptr<Node> mSkydromeNode;

    // Entities
    std::shared_ptr<LightEntity> mDirectionalLight;
    std::shared_ptr<LightEntity> mPointLight1;
    std::shared_ptr<LightEntity> mPointLight2;
    std::shared_ptr<LightEntity> mPointLight3;
    std::shared_ptr<SceneEntity> mScene;
    std::shared_ptr<SceneEntity> mSkydrome;
    std::shared_ptr<SceneEntity> mSnowman1;
    std::shared_ptr<SceneEntity> mSnowman2;
    std::shared_ptr<SceneEntity> mBox;

    // Movement
    double mBoxTheta;
    bool mMount;
};

}
