#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderMessageManager.h>

namespace FalconEngine
{

void
DebugRenderMessageManager::Update(double elapsed)
{
    auto tSecond = elapsed / 1000;

    for (auto messageIter = mMessageList.begin();
            messageIter != mMessageList.end(); )
    {
        // Compute left duration.
        messageIter->mDuration -= float(tSecond);
        if (messageIter->mDuration < 0)
        {
            auto messageIterPrevious = messageIter;
            ++messageIter;
            mMessageList.erase(messageIterPrevious);
        }
        else
        {
            ++messageIter;
        }
    }
}

}