#pragma once

namespace FalconEngine {

class InputHandler
{
public:

    size_t  m_priority;
    void   *m_caller;

    InputHandler()
        : m_priority(IN_DEFAULT)
        , m_caller(0)
    {

    }
};

}
