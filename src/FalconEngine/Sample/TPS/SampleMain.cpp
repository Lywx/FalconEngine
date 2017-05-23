#include "SampleGame.h"

using namespace std;

using namespace FalconEngine;

int main(int argc, char **argv)
{
    auto gameEngineSettings = GameEngineSettings::GetInstance();
    gameEngineSettings->mMouseVisible = true;
    gameEngineSettings->mMouseLimited = false;
    gameEngineSettings->mWindowWidth = 1600;
    gameEngineSettings->mWindowHeight = 900;

    SampleGame game;
    GameEngine gameEngine(&game);
    gameEngine.Run();

    return 0;
}

