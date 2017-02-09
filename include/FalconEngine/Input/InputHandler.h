#pragma once

namespace FalconEngine {

class InputHandler
{
public:

    size_t  mPriority;
    void   *mCaller;

    InputHandler()
        : mPriority(IN_DEFAULT)
        , mCaller(0)
    {

    }
};

}
