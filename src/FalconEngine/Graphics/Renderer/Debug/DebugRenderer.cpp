#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderer.h>

#include <FalconEngine/Core.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>
#include <FalconEngine/Graphics/Renderer/Resource/VertexBuffer.h>
#include <FalconEngine/Graphics/Renderer/Renderer.h>

using namespace std;

namespace FalconEngine
{

///************************************************************************/
///* Constructors and Destructor                                          */
///************************************************************************/
//DebugRenderer::DebugRenderer()
//{
//}
//
//DebugRenderer::~DebugRenderer()
//{
//}
//
///************************************************************************/
///* Rendering API                                                        */
///************************************************************************/
//void
//DebugRenderer::AddCircle(const Vector3f& center, const Vector3f& normal, float radius, Color color, float duration, bool depthEnabled)
//{
//}
//
//void
//DebugRenderer::AddCross(const Vector3f& position, Color color, float size, float duration, bool depthEnabled)
//{
//}
//
//void
//DebugRenderer::AddLine(const Vector3f& from, const Vector3f& to, Color color, float lineWidth, float duration, bool depthEnabled)
//{
//}
//
//void
//DebugRenderer::AddSphere(const Vector3f& center, float radius, Color color, float duration, bool depthEnabled)
//{
//}
//
///************************************************************************/
///* Rendering Engine API                                                 */
///************************************************************************/
//void
//DebugRenderer::Initialize()
//{
//    auto lineMaxNum = int(Kilobytes(10));
//
//    auto vertexBuffer = make_shared<VertexBuffer>(lineMaxNum * 2, sizeof(DebugVertex), BufferUsage::Stream);
//    auto visualEffect = make_shared<DebugEffect>();
//    auto vertexFormat = visualEffect->GetVertexFormat();
//    auto vertexGroup = make_shared<VertexGroup>();
//    vertexGroup->SetVertexBuffer(0, vertexBuffer, 0, vertexFormat->GetVertexBufferStride(0));
//
//    auto primitive = make_shared<PrimitiveLines>(vertexFormat, vertexGroup, nullptr, false);
//    auto visual = make_shared<Visual>(make_shared<Mesh>(primitive, nullptr));
//    auto visualEffectParams = make_shared<DebugEffectParams>();
//    visualEffect->CreateInstance(visual.get(), visualEffectParams);
//
//    mDebugBatch = make_shared<DebugRenderBatch>(vertexBuffer, visual);
//}
//
//void
//DebugRenderer::RenderBegin()
//{
//    mDebugBatch->mLineNum = 0;
//    mDebugBatch->mVertexBufferDataIndex = 0;
//}
//
//void
//DebugRenderer::Render(Renderer *renderer, double percent)
//{
//    if (mDebugBatch->mLineNum > 0)
//    {
//        // Update buffer data before drawing
//        int vertexNum = mDebugBatch->mLineNum * 2;
//        mDebugBatch->mVertexBuffer->SetElementNum(vertexNum);
//        renderer->Update(mDebugBatch->mVertexBuffer.get());
//        renderer->Draw(nullptr, mDebugBatch->mLines.get());
//    }
//}
//
//void
//DebugRenderer::RenderEnd()
//{
//}
//
void
DebugRenderer::Update(double /* elapsed */)
{
}

}
