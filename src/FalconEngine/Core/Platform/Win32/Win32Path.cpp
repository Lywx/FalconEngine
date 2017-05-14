#include <FalconEngine/Core/Path.h>

#if defined(FALCON_ENGINE_OS_WINDOWS)

using namespace std;

namespace FalconEngine
{

wstring
GetWString(const string& str)
{
    // NOTE(Wuxiang): http://en.cppreference.com/w/cpp/locale/codecvt_utf8_utf16
    using CodeOutput = wchar_t;
    using CodeConvert = codecvt_utf8_utf16<CodeOutput>;
    static wstring_convert<CodeConvert> sConverter;
    return sConverter.from_bytes(str);
}

}

#endif
