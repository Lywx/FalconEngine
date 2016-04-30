#pragma once

#include <iostream>
#include <iomanip>

#define DEBUG 1
#if DEBUG
#define TRACE_BLOCK() Trace trace_##__LINE__(__FUNCTION__)
#elif
#define TRACE_BLOCK()
#endif

class Trace
{
public:
    Trace(const char *function_name)
        : m_functionName (function_name)
    {
        PrintTime();
        std::cout << " " << m_functionName << " [+]" << std::endl;
    }

    ~Trace()
    {
        PrintTime();
        std::cout << " " << m_functionName << " [-]" << std::endl;
    }

private:
    const char *m_functionName;

    static void PrintTime()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::cout << std::put_time(&tm, "%H:%M:%S");
    }
};