#include <FalconEngine/Core/Path.h>

#if defined(FALCON_ENGINE_OS_LINUX)

using namespace std;

namespace FalconEngine
{

wstring
GetWString(const string& str)
{
    // NOTE(Wuxiang): Linux string works differently compared to Windows' counterpart.
    // Because default encoding in Linux is UTF-8, you could natively store UTF-8
    // encoded string in char in Linux. But the engine API still use wstring for supporting
    // both Windows and Linux at the same time.
    //
    // http://stackoverflow.com/questions/402283/stdwstring-vs-stdstring
    return wstring(str.begin(), str.end());
}

}

#endif
