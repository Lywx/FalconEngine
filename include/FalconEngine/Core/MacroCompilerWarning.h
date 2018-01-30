#pragma once

#define FALCON_ENGINE_CLASS_BEGIN \
__pragma(warning(disable: 4081)) \
__pragma(warning(disable: 4251)) \
__pragma(warning(disable: 4275)) \
class FALCON_ENGINE_API
#define FALCON_ENGINE_CLASS_END \
__pragma(warning(default: 4081)) \
__pragma(warning(default: 4251)) \
__pragma(warning(default: 4275))