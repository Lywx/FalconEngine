#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

#include <queue>

#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Shader/Shader.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformConstant.h>
#include <FalconEngine/Graphics/Renderer/Shader/ShaderUniformManual.h>

using namespace std;

namespace FalconEngine
{

FALCON_ENGINE_RTTI_IMPLEMENT(VisualEffect, Object);

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
VisualEffect::VisualEffect()
{
}

VisualEffect::~VisualEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
VisualEffect::InsertPass(std::unique_ptr<VisualEffectPass> pass)
{
    mPassList.push_back(move(pass));
}

const VisualEffectPass *
VisualEffect::GetPass(int passIndex) const
{
    return mPassList.at(passIndex).get();
}

VisualEffectPass *
VisualEffect::GetPass(int passIndex)
{
    return mPassList.at(passIndex).get();
}

int
VisualEffect::GetPassNum() const
{
    return int(mPassList.size());
}

Shader *
VisualEffect::GetShader(int passIndex)
{
    return mPassList.at(passIndex)->GetShader();
}

const BlendState *
VisualEffect::GetBlendState(int passIndex) const
{
    return mPassList.at(passIndex)->GetBlendState();
}

const CullState *
VisualEffect::GetCullState(int passIndex) const
{
    return mPassList.at(passIndex)->GetCullState();
}

const DepthTestState *
VisualEffect::GetDepthTestState(int passIndex) const
{
    return mPassList.at(passIndex)->GetDepthTestState();
}

const OffsetState *
VisualEffect::GetOffsetState(int passIndex) const
{
    return mPassList.at(passIndex)->GetOffsetState();
}

const StencilTestState *
VisualEffect::GetStencilTestState(int passIndex) const
{
    return mPassList.at(passIndex)->GetStencilTestState();
}

const WireframeState *
VisualEffect::GetWireframeState(int passIndex) const
{
    return mPassList.at(passIndex)->GetWireframeState();
}

std::shared_ptr<VertexFormat>
VisualEffectCreateVertexFormat()
{
    shared_ptr<VertexFormat> vertexFormat = make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Normal", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(2, "TexCoord", VertexAttributeType::FloatVec2, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

std::shared_ptr<VertexFormat>
VisualEffect::GetVertexFormat() const
{
    static shared_ptr<VertexFormat> sVertexFormat = VisualEffectCreateVertexFormat();
    return sVertexFormat;
}

void
VisualEffect::CheckEffectCompatible(VisualEffectInstance *instance) const
{
    if (!GetType().IsExactly(instance->GetEffect()->GetType()))
    {
        FALCON_ENGINE_THROW_SUPPORT_EXCEPTION();
    }
}

void
VisualEffect::CheckEffectSame(VisualEffect *effect) const
{
    if (this != effect)
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Effect is supposed to be the same.");
    }
}

void
VisualEffect::TraverseVisualLevelOrder(Node *node, std::function<void(Visual *)> visualOperation)
{
    using namespace std;

    queue<pair<Node *, int>> nodeQueueCurrent;
    queue<pair<Node *, int>> nodeQueueNext;

    // Use level order traversal to complete operation on each mesh.
    nodeQueueCurrent.push(make_pair(node, 1));
    while (!nodeQueueCurrent.empty())
    {
        // Complete traversing current level.
        while (!nodeQueueCurrent.empty())
        {
            auto renderItemCurrent = nodeQueueCurrent.front();
            auto renderNodeCurrent = renderItemCurrent.first;
            auto& sceneDepthCurrent = renderItemCurrent.second;

            nodeQueueCurrent.pop();

            // Visit the children.
            auto slotNum = renderNodeCurrent->GetChildrenSlotNum();
            for (auto slotIndex = 0; slotIndex < slotNum; ++slotIndex)
            {
                auto child = renderNodeCurrent->GetChildAt(slotIndex);
                if (auto childVisual = dynamic_pointer_cast<Visual>(child))
                {
                    // Perform the given operation only on Mesh child.
                    visualOperation(childVisual.get());
                }
                else if (auto childNode = dynamic_pointer_cast<Node>(child))
                {
                    // Prepare for traversing next level.
                    nodeQueueNext.push(make_pair(childNode.get(), sceneDepthCurrent + 1));
                }
                else
                {
                    // Scene graph only consists of two type of spatial objects:
                    // either Node or Visual.
                    FALCON_ENGINE_THROW_ASSERTION_EXCEPTION();
                }
            }
        }

        swap(nodeQueueCurrent, nodeQueueNext);
    }
}


}
