#include "SampleGame.h"

using namespace std;

using namespace FalconEngine;

int main(int argc, char **argv)
{
    SampleGame game;
    GameEngine gameEngine(&game);
    gameEngine.Run();

    return 0;
}

