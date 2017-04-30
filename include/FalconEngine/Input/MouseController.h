#pragma once

#include <FalconEngine/InputInclude.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class MouseControllerData;
using MouseControllerDataSharedPtr = std::shared_ptr<MouseControllerData>;

class MouseController final
{
public:
    MouseController();
    ~MouseController() = default;

public:
    void
    Initialize(MouseControllerDataSharedPtr data);

    void
    SetPosition(Vector2f position) const;

private:
    MouseControllerDataSharedPtr mData;
};

}