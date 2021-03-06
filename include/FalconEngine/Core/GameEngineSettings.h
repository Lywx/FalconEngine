#pragma once

#include <string>

#include <FalconEngine/Core/Macro.h>
#include <FalconEngine/Core/Memory.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN GameEngineSettings
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    FALCON_ENGINE_SINGLETON_LEAK_DECLARE(GameEngineSettings);

    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
private:
    GameEngineSettings();

public:
    virtual ~GameEngineSettings() = default;

public:
    /************************************************************************/
    /* Content                                                              */
    /************************************************************************/
    std::string mContentDirectory;
    std::string mShaderDirectory;

    /************************************************************************/
    /* Display                                                              */
    /************************************************************************/
    double      mFrameElapsedMillisecond;

    // If mouse event can be query outside game window.
    bool        mMouseLimited;

    // If mouse visible natively on game window.
    bool        mMouseVisible;

    bool        mWindowVisible;
    std::string mWindowTitle;
    int         mWindowWidth;
    int         mWindowHeight;
    float       mWindowNear;
    float       mWindowFar;

    bool        mDebugErrorBreak;

    bool        mTrace;
    std::string mTraceFile;
};
FALCON_ENGINE_CLASS_END

}
