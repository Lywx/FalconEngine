#pragma once

#include <FalconEngine/Graphics/SceneInclude.h>

namespace FalconEngine
{

class SceneEntity;
using SceneEntitySharedPtr = std::shared_ptr<SceneEntity>;

class SceneEntity : public Entity
{
public:
    explicit SceneEntity(NodeSharedPtr node);
    virtual ~SceneEntity() = default;
};

}