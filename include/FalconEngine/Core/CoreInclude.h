#pragma once

#include <climits>
#include <cstdint>

#include <boost/predef.h>

#if BOOST_OS_WINDOWS
#define FALCON_ENGINE_OS_WINDOWS 1
#elif BOOST_OS_LINUX
#define FALCON_ENGINE_OS_LINUX 1
#endif

#define FALCON_ENGINE_DEBUG_MEMORY 1

#define FALCON_ENGINE_NOT_SUPPORT() throw std::runtime_error("Operation is not supported.");
#define FALCON_ENGINE_NOT_POSSIBLE() assert(0);

#define IN
#define OUT
