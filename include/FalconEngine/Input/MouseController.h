#pragma once

#include <FalconEngine/Input/Header.h>
#include <FalconEngine/Math/Vector2.h>

namespace FalconEngine
{

class MouseControllerData;
using MouseControllerDataSharedPtr = std::shared_ptr<MouseControllerData>;

#pragma warning(disable: 4251)
class FALCON_ENGINE_API MouseController final
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
#pragma warning(default: 4251)

}