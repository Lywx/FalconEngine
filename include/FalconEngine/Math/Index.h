#pragma once

namespace FalconEngine {
namespace Math {

class Index
{
public:
    int A;
    int B;
    int C;

    Index() = default;
    Index(int a, int b, int c);

    Index(const Index& rhs) = default;
    Index(Index&& rhs) = default;

    ~Index() = default;
};

}
}