#pragma once

#include <string>

namespace FalconEngine {
namespace Core {

class GameDebug
{
public:
    static void OutputString(char *str);
    static void OutputString(std::string str);
};

}
}
