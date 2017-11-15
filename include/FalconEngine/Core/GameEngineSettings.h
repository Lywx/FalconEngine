#pragma once

#include <FalconEngine/Core/Common.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN GameEngineSettings
{
public:
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
    static GameEngineSettings *
    GetInstance()
    {
        static GameEngineSettings sInstance;
        return &sInstance;
    }

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

    // TODO(Wuxiang):
    bool        mOpenGLErrorBreak;

    bool        mTrace;
    std::string mTraceFile;
};
FALCON_ENGINE_CLASS_END

}
