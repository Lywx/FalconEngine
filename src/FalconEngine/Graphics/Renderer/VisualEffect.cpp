#include <FalconEngine/Graphics/Renderer/VisualEffect.h>

#include <queue>

#include <FalconEngine/Graphics/Renderer/Camera.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectPass.h>
#include <FalconEngine/Graphics/Renderer/VisualEffectInstance.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexAttribute.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexFormat.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexGroup.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture1d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2d.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture2dArray.h>
#include <FalconEngine/Graphics/Renderer/Resource/Texture3d.h>
#include <FalconEngine/Graphics/Renderer/Scene/Node.h>
#include <FalconEngine/Graphics/Renderer/Scene/Visual.h>
#include <FalconEngine/Graphics/Renderer/State/BlendState.h>
#include <FalconEngine/Graphics/Renderer/State/CullState.h>
#include <FalconEngine/Graphics/Renderer/State/DepthTestState.h>
#include <FalconEngine/Graphics/Renderer/State/OffsetState.h>
#include <FalconEngine/Graphics/Renderer/State/StencilTestState.h>
#include <FalconEngine/Graphics/Renderer/State/WireframeState.h>
#include <FalconEngine/Graphics/Renderer/Resource/Shader.h>
#include <FalconEngine/Graphics/Renderer/Resource/Uniform.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformAutomatic.h>
#include <FalconEngine/Graphics/Renderer/Resource/UniformManual.h>

using namespace std;

namespace FalconEngine
{

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
    FALCON_ENGINE_CHECK_NULLPTR(pass->GetShader());
    FALCON_ENGINE_CHECK_NULLPTR(pass->GetShaderVertexFormat());

    mEffectPassList.push_back(move(pass));
}

const VisualEffectPass *
VisualEffect::GetPass(int passIndex) const
{
    return mEffectPassList.at(passIndex).get();
}

VisualEffectPass *
VisualEffect::GetPass(int passIndex)
{
    return mEffectPassList.at(passIndex).get();
}

int
VisualEffect::GetPassNum() const
{
    return int(mEffectPassList.size());
}

Shader *
VisualEffect::GetShader(int passIndex)
{
    return mEffectPassList.at(passIndex)->GetShader();
}

const BlendState *
VisualEffect::GetBlendState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetBlendState();
}

const CullState *
VisualEffect::GetCullState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetCullState();
}

const DepthTestState *
VisualEffect::GetDepthTestState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetDepthTestState();
}

const OffsetState *
VisualEffect::GetOffsetState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetOffsetState();
}

const StencilTestState *
VisualEffect::GetStencilTestState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetStencilTestState();
}

const WireframeState *
VisualEffect::GetWireframeState(int passIndex) const
{
    return mEffectPassList.at(passIndex)->GetWireframeState();
}

/************************************************************************/
/* Effect Instancing Utility                                            */
/************************************************************************/
std::shared_ptr<const VisualEffect>
VisualEffect::GetEffect() const
{
    return shared_from_this();
}

std::shared_ptr<VisualEffect>
VisualEffect::GetEffect()
{
    return shared_from_this();
}

std::shared_ptr<FalconEngine::VisualEffectInstance>
VisualEffect::CreateInstance()
{
    auto visualEffectInstance = std::make_shared<FalconEngine::VisualEffectInstance>(GetEffect());
    return visualEffectInstance;
}

void
VisualEffect::CheckVertexFormatCompatible(const Visual *visual) const
{
    auto const vertexFormat = visual->GetVertexFormat();
    if (vertexFormat)
    {
        // NOTE(Wuxiang): Allow users to provide their own vertex format as
        // long as the vertex format is compatible with effect's requirement.
        // Because the user should know the requirement of specific shader before
        // they provide visual to use that shader effect. The user should be able
        // to customize the binding index of vertex format and use much more
        // flexible buffer arrangement if they need that benefit.

        auto const passNum = GetPassNum();
        for (auto passIndex = 0; passIndex < passNum; ++passIndex)
        {
            auto const passVertexFormat = GetPass(passIndex)->GetShaderVertexFormat();
            if (!vertexFormat->IsVertexAttributeCompatible(passVertexFormat))
            {
                FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Vertex format is not compatible.");
            }
        }
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Visual is not correctly initialized.");
    }
}

void
VisualEffect::CheckVertexGroupCompatible(Visual *visual) const
{
    auto vertexGroup = visual->GetVertexGroup();
    if (vertexGroup)
    {
        auto const passNum = GetPassNum();
        for (auto passIndex = 0; passIndex < passNum; ++passIndex)
        {
            auto const passVertexFormat = GetPass(passIndex)->GetShaderVertexFormat();
            if (!passVertexFormat->IsVertexBindingCompatible(vertexGroup))
            {
                FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Vertex group is not compatible.");
            }
        }
    }
    else
    {
        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION("Visual is not correctly initialized.");
    }
}

/************************************************************************/
/* Effect Instancing Utility                                            */
/************************************************************************/
void
VisualEffect::TraverseLevelOrder(Node *node, std::function<void(Visual *visual)> visit) const
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
                if (auto childVisual = dynamic_cast<Visual *>(child))
                {
                    // Perform the given operation only on Mesh child.
                    visit(childVisual);
                }
                else if (auto childNode = dynamic_cast<Node *>(child))
                {
                    // Prepare for traversing next level.
                    nodeQueueNext.push(make_pair(childNode, sceneDepthCurrent + 1));
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

/************************************************************************/
/* Shader Uniform Utility                                               */
/************************************************************************/
void
VisualEffect::SetUniformAutomaticModelTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix4f>(uniformName,
                                           std::bind([](const Visual * visual, const Camera * /* camera */)
    {
        return visual->mWorldTransform;
    }, _1, _2)));
}

void
VisualEffect::SetUniformAutomaticModelViewTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix4f>(uniformName,
                                           std::bind([](const Visual * visual, const Camera * camera)
    {
        return camera->GetView() * visual->mWorldTransform;
    }, _1, _2)));
}

void
VisualEffect::SetUniformAutomaticModelViewProjectionTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix4f>(uniformName, std::bind([](const Visual * visual, const Camera * camera)
    {
        return camera->GetViewProjection() * visual->mWorldTransform;
    }, _1, _2)));
}

void
VisualEffect::SetUniformAutomaticViewProjectionTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix4f>(uniformName, std::bind([](const Visual * /* visual */, const Camera * camera)
    {
        return camera->GetViewProjection();
    }, _1, _2)));
}

void
VisualEffect::SetUniformAutomaticNormalTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix3f>(uniformName,
                                           std::bind([](const Visual * visual, const Camera * camera)
    {
        auto normalTransform = Matrix4f::Transpose(Matrix4f::Inverse(camera->GetView() * visual->mWorldTransform));
        return Matrix3f(normalTransform);
    }, _1, _2)));
}

void
VisualEffect::SetUniformAutomaticScreenTransform(VisualEffectInstance *visualEffectInstance, int passIndex, const std::string& uniformName) const
{
    using namespace std;
    using namespace std::placeholders;

    visualEffectInstance->SetUniform(passIndex, ShareUniformAutomatic<Matrix4f>(uniformName,
                                           std::bind([](const Visual *, const Camera *)
    {
        static auto sMasterRenderer = Renderer::GetInstance();
        auto viewport = sMasterRenderer->GetViewport();

        float wOver2 = 0.5f * viewport->GetWidth();
        float hOver2 = 0.5f * viewport->GetHeight();
        float l = viewport->mLeft;
        float b = viewport->mBottom;
        float nOver2 = 0.5f * viewport->mNear;
        float fOver2 = 0.5f * viewport->mFar;

        Matrix4f screenTransform = Matrix4f::Identity;
        screenTransform[0][0] = wOver2;
        screenTransform[1][1] = hOver2;
        screenTransform[2][2] = fOver2 - nOver2;
        screenTransform[3][0] = wOver2 + l;
        screenTransform[3][1] = hOver2 + b;
        screenTransform[3][2] = fOver2 + nOver2;
        return screenTransform;
    }, _1, _2)));
}

}
