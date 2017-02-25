#include "SampleGame.h"

using namespace std;

using namespace FalconEngine;

int main(int argc, char **argv)
{
    auto game = Sample::SampleGame();
    auto gameEngine = GameEngine(&game);
    gameEngine.Run();

    return 0;
}

