#include <FalconEngine/Context/GameEngineInput.h>

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
GameEngineInput::GameEngineInput() :
    mKeyboard(nullptr),
    mMouse(nullptr)
{

}

GameEngineInput::~GameEngineInput()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineInput::Initialize(const GameEngineData *data, GameEngineInputSettingsSharedPtr settings)
{
    mSettings = settings;

    InitializePlatform(data);
}

std::shared_ptr<Keyboard>
GameEngineInput::CreateKeyboard()
{
    if (mKeyboard)
    {
        return mKeyboard;
    }

    mKeyboard = std::make_shared<Keyboard>();
    mKeyboard->Initialize(false);
    return mKeyboard;

}

void
GameEngineInput::Update(float elapsed)
{
}
}
