#include <FalconEngine/Core/GameEngineInput.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <Windows.h>

namespace FalconEngine
{

void
GameEngineInput::PollEventPlatform()
{
    MSG msg = {};
    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

}

#endif