#pragma once

#include <type_traits>

// NOTE(Wuxiang): Math library use right-handed system in GLM Library.
#ifdef GLM_FORCE_LEFT_HANDED
#undef GLM_FORCE_LEFT_HANDED
#endif

#include <FalconEngine/MathInclude.h>
#include <FalconEngine/Math/Color.h>
#include <FalconEngine/Math/Constant.h>
#include <FalconEngine/Math/Function.h>
#include <FalconEngine/Math/Handedness.h>
#include <FalconEngine/Math/Integer.h>
#include <FalconEngine/Math/Matrix4.h>
#include <FalconEngine/Math/Quaternion.h>
#include <FalconEngine/Math/Rectangle.h>
#include <FalconEngine/Math/Vector2.h>
#include <FalconEngine/Math/Vector3.h>
#include <FalconEngine/Math/Vector4.h>
