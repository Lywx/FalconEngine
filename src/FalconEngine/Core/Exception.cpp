#include <FalconEngine/Core/Exception.h>
#include <FalconEngine/Core/Debug.h>

namespace FalconEngine
{

RuntimeException::RuntimeException(const std::string& message) :
    runtime_error(message)
{
    // TODO(Wuxiang): 2017-10-27 15:45 Read about exception in multi-threading.
    Debug::OutputStringInternal(message);
}

APIError::APIError(const std::string& message) :
    RuntimeException(message)
{
    exit(FALCON_ENGINE_API_ERROR);
}

AssertionError::AssertionError(const std::string& message) :
    RuntimeException(message)
{
    exit(FALCON_ENGINE_ASSERTION_ERROR);
}

}
