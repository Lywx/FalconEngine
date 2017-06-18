#include <FalconEngine/Graphics/Effect/DebugEffect.h>

using namespace std;

namespace FalconEngine
{

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
DebugEffect::DebugEffect()
{
}

DebugEffect::~DebugEffect()
{
}

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
DebugEffect::CreateInstance(Visual *visual, std::shared_ptr<DebugEffectParams> params) const
{
    auto instance = InstallInstance(visual, params);
    InitializeInstance(instance.get(), params);
}

std::shared_ptr<VertexFormat>
DebugEffect::GetVertexFormat() const
{
    static shared_ptr<VertexFormat> sVertexFormat = CreateVertexFormat();
    return sVertexFormat;
}

/************************************************************************/
/* Protected Members                                                    */
/************************************************************************/
std::shared_ptr<VertexFormat>
DebugEffect::CreateVertexFormat() const
{
    auto vertexFormat = std::make_shared<VertexFormat>();
    vertexFormat->PushVertexAttribute(0, "Position", VertexAttributeType::FloatVec3, false, 0);
    vertexFormat->PushVertexAttribute(1, "Color", VertexAttributeType::FloatVec4, false, 0);
    vertexFormat->FinishVertexAttribute();
    return vertexFormat;
}

void
DebugEffect::InitializeInstance(VisualEffectInstance *instance, std::shared_ptr<DebugEffectParams> params) const
{
    SetShaderUniformAutomaticModelViewTransform(instance, 0, "ViewProjectionTransform");
}

}
