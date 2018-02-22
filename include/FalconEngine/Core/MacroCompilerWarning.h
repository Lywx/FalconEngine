#pragma once

#define FALCON_ENGINE_PROGMA_BEGIN \
__pragma(warning(disable: 4081)) \
__pragma(warning(disable: 4251)) \
__pragma(warning(disable: 4275))

#define FALCON_ENGINE_PROGMA_END \
__pragma(warning(default: 4081)) \
__pragma(warning(default: 4251)) \
__pragma(warning(default: 4275))

#define FALCON_ENGINE_CLASS_BEGIN \
FALCON_ENGINE_PROGMA_BEGIN \
class FALCON_ENGINE_API

#define FALCON_ENGINE_CLASS_END \
FALCON_ENGINE_PROGMA_END

#define FALCON_ENGINE_STRUCT_BEGIN \
__pragma(pack(push, 1)) \
struct FALCON_ENGINE_API

#define FALCON_ENGINE_STRUCT_END \
__pragma(pack(pop))

