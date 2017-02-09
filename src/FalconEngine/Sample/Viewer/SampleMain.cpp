#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <climits>
#include <vector>

#include <FalconEngine/Context.h>
#include <FalconEngine/Context.h>

using namespace std;

namespace FalconEngine
{
namespace Sample
{

int main(int argc, char **argv)
{
    auto game = Game();
    auto gameEngine = GameEngine(&game);
    gameEngine.Run();

    return 0;
}

}
}

