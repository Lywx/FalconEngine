#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <memory>

#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Debug/DebugRenderBatch.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class DebugRendererHelper
{
public:
    static const int SphereSampleNum;
    static const int CircleSampleNum;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static std::shared_ptr<DebugRenderLineBatch>
    CreateBatch(std::shared_ptr<DebugEffect> visualEffect);

    static void
    FillAABB(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
             _IN_OUT_ unsigned char                 *bufferData,

             _IN_ const Vector3f& min,
             _IN_ const Vector3f& max,
             _IN_ const Color&    color);

    static void
    FillColor(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
              _IN_OUT_ unsigned char                 *bufferData,

              _IN_ const Color& color)
    {
        bufferAdaptor->Fill(bufferData, Vector4f(color));
    }

    static void
    FillCircle(_IN_OUT_ std::shared_ptr<BufferAdaptor>& bufferAdaptor,
               _IN_OUT_ unsigned char                  *bufferData,

               _IN_ const Vector3f& center,
               _IN_ const Vector3f& normal,
               _IN_ float           radius,
               _IN_ const Color&    color);

    static void
    FillCross(_IN_OUT_ std::shared_ptr<BufferAdaptor>& bufferAdaptor,
              _IN_OUT_ unsigned char                  *bufferData,

              _IN_ const Vector3f& center,
              _IN_ float           radius,
              _IN_ const Color&    color);

    static void
    FillLine(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
             _IN_OUT_ unsigned char                 *bufferData,

             _IN_ const Vector3f& from,
             _IN_ const Vector3f& to,
             _IN_ const Color&    color)
    {
        FillPoint(bufferAdaptor, bufferData, from, color);
        FillPoint(bufferAdaptor, bufferData, to, color);
    }

    static void
    FillPoint(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
              _IN_OUT_ unsigned char                 *bufferData,

              _IN_ const Vector3f& position,
              _IN_ const Color&    color
             )
    {
        FillPosition(bufferAdaptor, bufferData, position);
        FillColor(bufferAdaptor, bufferData, color);
    }

    static void
    FillPosition(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
                 _IN_OUT_ unsigned char                 *bufferData,

                 _IN_ const Vector3f& position)
    {
        bufferAdaptor->Fill(bufferData, position);
    }

    static void
    FillSphere(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
               _IN_OUT_ unsigned char                 *bufferData,

               _IN_ const Vector3f& center,
               _IN_ float           radius,
               _IN_ const Color&    color);

    static void
    FillTriangle(_IN_OUT_ std::shared_ptr<BufferAdaptor> bufferAdaptor,
                 _IN_OUT_ unsigned char                 *bufferData,

                 _IN_ const Vector3f& position1,
                 _IN_ const Vector3f& position2,
                 _IN_ const Vector3f& position3,
                 _IN_ const Color&    color)
    {
        FillPoint(bufferAdaptor, bufferData, position1, color);
        FillPoint(bufferAdaptor, bufferData, position2, color);
        FillPoint(bufferAdaptor, bufferData, position3, color);
    }
};
}
