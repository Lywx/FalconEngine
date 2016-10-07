#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <limits.h>
#include <vector>

#include <boost/predef.h>

#include "Visualizer.cpp"

using namespace FalconEngine;

int
main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Argument is invalid. Argument: <vertexFilename> <indexFilename>."
                  << std::endl;
        return -1;
    }

    auto vertexFileNameString = std::string(argv[1]);
    auto vertexFileNameWString = std::wstring(
                                     vertexFileNameString.begin(),
                                     vertexFileNameString.end());

    auto indexFileiNameString = std::string(argv[2]);
    auto indexFileiNameWString = std::wstring(
                                     indexFileiNameString.begin(),
                                     indexFileiNameString.end());

    if (!Exists(vertexFileNameWString)
            || !Exists(indexFileiNameWString))
    {
        std::cout << "Files don't exist." << std::endl;
        return -1;
    }

    Visualizer game(vertexFileNameWString, indexFileiNameWString);
    GameEngine engine(&game);
    engine.Run();

    return 0;
}

#ifdef BOOST_OS_WINDOWS
#include <windows.h>
int WinMain(
    HINSTANCE instance,
    HINSTANCE previousInstance,
    LPSTR     cmdLine,
    int       cmdShow
)
{
    std::istringstream       cmdStream(cmdLine);
    std::vector<std::string> cmdTokens{ std::istream_iterator<std::string>{cmdStream},
                                        std::istream_iterator<std::string>{} };

    // argv[0] = program name
    char *cmdArgv[3] = { "MeshVisualzer.exe" };

    for (auto i = 0; i < cmdTokens.size(); ++i)
    {
        cmdArgv[i + 1] = const_cast<char *>(cmdTokens[i].c_str());
    }

    // argc = 1 + parameters' size
    // argv[] = program name + parameters
    main(int(cmdTokens.size() + 1), cmdArgv);
}

#endif