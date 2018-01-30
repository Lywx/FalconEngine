#pragma once

#include <FalconEngine/Core/Common.h>

#include <string>
#include <mutex>

#include <FalconEngine/Core/Debug.h>
#include <FalconEngine/Core/Trace.h>

namespace FalconEngine
{

FALCON_ENGINE_CLASS_BEGIN GameEngineDebugger
{
    /************************************************************************/
    /* Static Members                                                       */
    /************************************************************************/
public:
    static GameEngineDebugger *
    GetInstance()
    {
        static GameEngineDebugger sInstance;
        return &sInstance;
    }

    static void
    Break()
    {
        std::lock_guard<std::mutex> lock(sMutex);

        Debug::Break();
    }

    static void
    OutputString(const char *str)
    {
        std::lock_guard<std::mutex> lock(sMutex);

        Debug::OutputString(str);
    }

    static void
    OutputString(const std::string & str)
    {
        std::lock_guard<std::mutex> lock(sMutex);

        Debug::OutputString(str);
    }

    template<class ... Args>
    static void
    OutputStringFormat(const char *format, Args&& ... args)
    {
        std::lock_guard<std::mutex> lock(sMutex);

        Debug::OutputStringFormat(format, std::forward<Args>(args)...);
    }


private:
    /************************************************************************/
    /* Constructors and Destructor                                          */
    /************************************************************************/
    GameEngineDebugger();

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    void
    Initialize();

private:
    static std::mutex sMutex;
    bool              mInitialized = false;
};
FALCON_ENGINE_CLASS_END

}
