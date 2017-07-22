#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessageManager.h>

namespace FalconEngine
{

void
DebugRenderMessageManager::Update(double elapsed)
{
    auto tSecond = elapsed / 1000;

    for (auto& message : mMessageList)
    {
        // Compute left duration.
        message.mDuration -= float(tSecond);
        if (message.mDuration < 0)
        {
            mMessageList.remove(message);
        }
    }
}

}