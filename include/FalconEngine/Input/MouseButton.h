#pragma once

#include <FalconEngine/InputInclude.h>

#include <functional>

namespace FalconEngine
{

enum class MouseButton
{
    LeftButton = 0,
    RightButton = 1,
    MiddleButton = 2
};

using MouseButtonHash = std::hash<int>;

}

namespace std
{

template <>
struct hash<FalconEngine::MouseButton>
{
    size_t operator()(const FalconEngine::MouseButton& button) const
    {
        return FalconEngine::MouseButtonHash {} (int(button));
    }
};

}
