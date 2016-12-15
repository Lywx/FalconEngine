#pragma once

#include <FalconEngine/Graphics/Scenes/Spatial.h>

namespace FalconEngine
{

class Visual : public Spatial
{
protected:
    Visual();

public:
    virtual ~Visual();

protected:
    virtual void UpdateWorldBound() override;
    virtual void UpdateModelBound();
};

typedef std::shared_ptr<Visual> VisualPtr;

}
