#include <FalconEngine/Graphics/Renderer/Debug/DebugRendererHelper.h>

#include <FalconEngine/Core/Memory.h>
#include <FalconEngine/Graphics/Renderer/PrimitiveLines.h>

using namespace std;

namespace FalconEngine
{

const int
DebugRendererHelper::CircleSampleNum = 16;

const int
DebugRendererHelper::SpherePhiSampleNum = 16;

const int
DebugRendererHelper::SphereThetaSampleNum = 8;

/************************************************************************/
/* Public Members                                                       */
/************************************************************************/
void
DebugRendererHelper::FillAABB(BufferAdaptor  *bufferAdaptor,
                              unsigned char  *bufferData,
                              const Vector3f& min,
                              const Vector3f& max,
                              const Color&    color)
{
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, min.y, min.z),
             Vector3f(max.x, min.y, min.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, max.y, min.z),
             Vector3f(max.x, max.y, min.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, min.y, max.z),
             Vector3f(max.x, min.y, max.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, max.y, max.z),
             Vector3f(max.x, max.y, max.z), color);

    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, min.y, min.z),
             Vector3f(min.x, max.y, min.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(max.x, min.y, min.z),
             Vector3f(max.x, max.y, min.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, min.y, max.z),
             Vector3f(min.x, max.y, max.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(max.x, min.y, max.z),
             Vector3f(max.x, max.y, max.z), color);

    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, min.y, min.z),
             Vector3f(min.x, min.y, max.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(min.x, max.y, min.z),
             Vector3f(min.x, max.y, max.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(max.x, min.y, min.z),
             Vector3f(max.x, min.y, max.z), color);
    FillLine(bufferAdaptor, bufferData,
             Vector3f(max.x, max.y, min.z),
             Vector3f(max.x, max.y, max.z), color);
}

// @params u, v Those must be unit vector.
inline Vector3f
CirclePosition(float theta, float radius, const Vector3f& u, const Vector3f& v)
{
    return radius * (u * sin(theta) + v * cos(theta));
}

void
DebugRendererHelper::FillCircle(BufferAdaptor  *bufferAdaptor,
                                unsigned char  *bufferData,

                                const Vector3f& center,
                                const Vector3f& normal,
                                float           radius,
                                const Color&    color)
{
    auto thetaStep = float(2 * Pi / CircleSampleNum);

    // NOTE(Wuxiang): Get U, V, which is orthogonal base vector on linear space
    // orthogonal to given normal vector, by solving AX = 0, where:
    // A = [A B C], X = [x].
    //     [0 0 0]      [y]
    //     [0 0 0]      [z]
    //
    // Then finish Schmidt process to orthogonalise and normalize those vectors.
    Vector3f u(-normal.y / normal.x, 1.0f, 0.0f);
    Vector3f v(-normal.z / normal.x, 0.0f, 1.0f);

    auto uNormalized = Vector3f::Normalize(u);
    auto vProjection = Vector3f::Dot(uNormalized, v);

    // This is not only normalized but orthogonalised.
    auto vNormalized = Vector3f::Normalize(v - vProjection * uNormalized);

    for (int thetaIndex = 0; thetaIndex < CircleSampleNum; ++thetaIndex)
    {
        float theta = thetaStep * thetaIndex;
        float thetaNext = thetaIndex + 1 == CircleSampleNum
                          ? 2 * Pi
                          : thetaStep * (thetaIndex + 1);;

        FillLine(bufferAdaptor, bufferData,
                 center + CirclePosition(theta, radius, uNormalized, vNormalized),
                 center + CirclePosition(thetaNext, radius, uNormalized, vNormalized), color);
    }
}

void
DebugRendererHelper::FillCross(BufferAdaptor  *bufferAdaptor,
                               unsigned char  *bufferData,

                               const Vector3f& center,
                               float           radius,
                               const Color&    color)
{
    FillLine(bufferAdaptor, bufferData,
             center + Vector3f(radius, 0, 0),
             center + Vector3f(-radius, 0, 0), color);

    FillLine(bufferAdaptor, bufferData,
             center + Vector3f(0, radius, 0),
             center + Vector3f(0, -radius, 0), color);

    FillLine(bufferAdaptor, bufferData,
             center + Vector3f(0, 0, radius),
             center + Vector3f(0, 0, -radius), color);
}

inline Vector3f
SpherePosition(float radius, float theta, float phi)
{
    return radius * Vector3f(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

void
DebugRendererHelper::FillSphere(BufferAdaptor  *bufferAdaptor,
                                unsigned char  *bufferData,
                                const Vector3f& center,
                                float           radius,
                                const Color&    color)
{
    auto thetaStep = float(Pi / SphereThetaSampleNum);
    auto phiStep = float(2 * Pi / SpherePhiSampleNum);

    for (auto thetaIndex = 0; thetaIndex < SphereThetaSampleNum; ++thetaIndex)
    {
        float theta = thetaStep * thetaIndex;
        float thetaNext = thetaIndex + 1 == SphereThetaSampleNum
                          ? Pi
                          : (thetaIndex + 1) * thetaStep;

        for (auto phiIndex = 0; phiIndex < SpherePhiSampleNum; ++phiIndex)
        {
            float phi = phiStep * phiIndex;
            float phiNext = phiIndex + 1 == SpherePhiSampleNum
                            ? 2 * Pi
                            : (phiIndex + 1) * phiStep;

            auto p0 = center + SpherePosition(radius, theta, phi);
            auto p1 = center + SpherePosition(radius, theta, phiNext);
            auto p2 = center + SpherePosition(radius, thetaNext, phi);
            auto p3 = center + SpherePosition(radius, thetaNext, phiNext);

            FillTriangle(bufferAdaptor, bufferData, p0, p1, p2, color);
            FillTriangle(bufferAdaptor, bufferData, p1, p3, p2, color);
        }
    }
}

}
