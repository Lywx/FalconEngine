#pragma once

#include <FalconEngine/Context/Common.h>

namespace FalconEngine
{

#pragma warning(disable: 4251)
class FALCON_ENGINE_API GameEngineSettings
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
};
#pragma warning(default: 4251)

}
