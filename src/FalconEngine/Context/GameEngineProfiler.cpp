#include <FalconEngine/Context/GameEngineProfiler.h>

namespace FalconEngine
{

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
GameEngineProfiler::Initialize(GameEngineData * /* gameEngineData */, GameEngineSettings * /* gameEngineSettings */)
{
}

double
GameEngineProfiler::GetLastFrameElapsedMillisecond() const
{
    return mLastFrameElapsedMillisecond;
}

double
GameEngineProfiler::GetLastFrameFPS() const
{
    return mLastFrameFPS;
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
