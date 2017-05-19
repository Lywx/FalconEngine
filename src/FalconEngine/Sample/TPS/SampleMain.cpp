#include "SampleGame.h"

using namespace std;

using namespace FalconEngine;

int main(int argc, char **argv)
{
    auto gameEngineSettings = make_shared<GameEngineSettings>();
    gameEngineSettings->mGraphics->mWidth = 1600;
    gameEngineSettings->mGraphics->mHeight = 900;

    SampleGame game;
    game.SetEngineSettings(gameEngineSettings);

    GameEngine gameEngine(&game);
    gameEngine.Run();

    return 0;
}

