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
    AssetManager              *mAssetManager;

    FirstPersonCameraSharedPtr mCamera;

    const BitmapFont          *mFontConsole;
    const BitmapFont          *mFontDisplay;

    HandednessRight            mHandedness;

    Model                     *mModelNanosuit;
    EntitySharedPtr            mModelPerson;

    NodeSharedPtr              mScene;
};

}
