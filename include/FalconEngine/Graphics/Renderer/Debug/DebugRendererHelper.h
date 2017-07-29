#pragma once

#include <FalconEngine/Graphics/Common.h>

#include <memory>

#include <FalconEngine/Graphics/Effect/DebugEffect.h>
#include <FalconEngine/Graphics/Renderer/Resource/BufferAdaptor.h>

namespace FalconEngine
{

class DebugRendererHelper
{
public:
    static const int SpherePhiSampleNum;
    static const int SphereThetaSampleNum;
    static const int CircleSampleNum;

public:
    /************************************************************************/
    /* Public Members                                                       */
    /************************************************************************/
    static void
    FillAABB(_IN_OUT_ BufferAdaptor *bufferAdaptor,
             _IN_OUT_ unsigned char *bufferData,

             _IN_ const Vector3f& min,
             _IN_ const Vector3f& max,
             _IN_ const Color&    color,
             _IN_ int             cameraIndex);

    static void
    FillColor(_IN_OUT_ BufferAdaptor *bufferAdaptor,
              _IN_OUT_ unsigned char *bufferData,

              _IN_ const Color& color)
    {
        bufferAdaptor->Fill(bufferData, Vector4f(color));
    }

    static void
    FillCircle(_IN_OUT_ BufferAdaptor *bufferAdaptor,
               _IN_OUT_ unsigned char *bufferData,

               _IN_ const Vector3f& center,
               _IN_ const Vector3f& normal,
               _IN_ float           radius,
               _IN_ const Color&    color,
               _IN_ int             cameraIndex);

    static void
    FillCross(_IN_OUT_ BufferAdaptor *bufferAdaptor,
              _IN_OUT_ unsigned char *bufferData,

              _IN_ const Vector3f& center,
              _IN_ float           radius,
              _IN_ const Color&    color,
              _IN_ int             cameraIndex);

    static void
    FillLine(_IN_OUT_ BufferAdaptor *bufferAdaptor,
             _IN_OUT_ unsigned char *bufferData,

             _IN_ const Vector3f& from,
             _IN_ const Vector3f& to,
             _IN_ const Color&    color,
             _IN_ int             cameraIndex)
    {
        FillPoint(bufferAdaptor, bufferData, from, color, cameraIndex);
        FillPoint(bufferAdaptor, bufferData, to, color, cameraIndex);
    }

    static void
    FillCamera(_IN_OUT_ BufferAdaptor *bufferAdaptor,
               _IN_OUT_ unsigned char *bufferData,
               _IN_     int            cameraIndex)
    {
        bufferAdaptor->Fill(bufferData, cameraIndex);
    }

    static void
    FillPoint(_IN_OUT_ BufferAdaptor *bufferAdaptor,
              _IN_OUT_ unsigned char *bufferData,

              _IN_ const Vector3f& position,
              _IN_ const Color&    color,
              int                  cameraIndex)
    {
        FillPosition(bufferAdaptor, bufferData, position);
        FillColor(bufferAdaptor, bufferData, color);
        FillCamera(bufferAdaptor, bufferData, cameraIndex);
    }

    static void
    FillPosition(_IN_OUT_ BufferAdaptor *bufferAdaptor,
                 _IN_OUT_ unsigned char *bufferData,

                 _IN_ const Vector3f& position)
    {
        bufferAdaptor->Fill(bufferData, position);
    }

    static void
    FillSphere(_IN_OUT_ BufferAdaptor *bufferAdaptor,
               _IN_OUT_ unsigned char *bufferData,

               _IN_ const Vector3f& center,
               _IN_ float           radius,
               _IN_ const Color&    color,
               _IN_ int             cameraIndex);

    static void
    FillTriangle(_IN_OUT_ BufferAdaptor *bufferAdaptor,
                 _IN_OUT_ unsigned char *bufferData,

                 _IN_ const Vector3f& position1,
                 _IN_ const Vector3f& position2,
                 _IN_ const Vector3f& position3,
                 _IN_ const Color&    color,
                 _IN_ int             cameraIndex)
    {
        FillPoint(bufferAdaptor, bufferData, position1, color, cameraIndex);
        FillPoint(bufferAdaptor, bufferData, position2, color, cameraIndex);
        FillPoint(bufferAdaptor, bufferData, position3, color, cameraIndex);
    }
};
}
