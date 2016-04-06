#include <FalconEngine/Vector4.h>

namespace FalconEngine {
namespace Math {

const Vector4 Vector4::Zero = glm::vec4(0.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::UnitX = glm::vec4(1.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::UnitY = glm::vec4(0.f, 1.f, 0.f, 0.f);
const Vector4 Vector4::UnitZ = glm::vec4(0.f, 0.f, 1.f, 0.f);
const Vector4 Vector4::UnitW = glm::vec4(0.f, 0.f, 0.f, 1.f);

}
}

