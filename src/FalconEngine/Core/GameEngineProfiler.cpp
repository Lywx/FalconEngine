#include <FalconEngine/Core/GameEngineProfiler.h>

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineProfiler::Initialize()
{
}

double
GameEngineProfiler::GetLastFrameElapsedMillisecond() const
{
    return mLastFrameElapsedMillisecond;
}

double
GameEngineProfiler::GetLastFrameFps() const
{
    return mLastFrameFps;
}

double
GameEngineProfiler::GetLastFrameUpdateTotalCount() const
{
    return mLastFrameUpdateTotalCount;
}

double
GameEngineProfiler::GetLastUpdateElapsedMillisecond() const
{
    return mLastUpdateElapsedMillisecond;
}

double
GameEngineProfiler::GetLastRenderElapsedMillisecond() const
{
    return mLastRenderElapsedMillisecond;
}

}
