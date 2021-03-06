#include <FalconEngine/Platform/Win32/Win32Exception.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <FalconEngine/Core/Exception.h>

#include <comdef.h>
#include <Windows.h>

namespace FalconEngine
{

void
D3DCheckSuccess(HRESULT hr)
{
    if (FAILED(hr))
    {
        _com_error err(hr);

        FALCON_ENGINE_THROW_RUNTIME_EXCEPTION(err.ErrorMessage());
    }
}

}

#endif