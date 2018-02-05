#include <FalconEngine/Input/KeyboardState.h>

#if defined(FALCON_ENGINE_WINDOW_WIN32)
#include <vector>

namespace FalconEngine
{

std::vector<unsigned int>
CreateKeyList()
{
    // NOTE(Wuxiang): Copy from the Key enum value.
    std::vector<unsigned int> keyCode = { 340, 341, 342, 344, 345, 346, };

    // HACK(Wuxiang): Windows API.
    for (unsigned int i = 0; i < 0xFF; ++i)
    {
        keyCode.push_back(i);
    }

    return keyCode;
}

/************************************************************************/
/* Constructors and Destructor                                          */
/************************************************************************/
KeyboardState::KeyboardState()
{
    // NOTE(Wuxiang): Copy from the Key enum value.
    static std::vector<unsigned int> sKeyList = CreateKeyList();

    int keyNum = int(sKeyList.size());
    for (int keyIndex = 0; keyIndex < keyNum; ++keyIndex)
    {
        auto key = Key(sKeyList[keyIndex]);
        insert({ key, KeyState(key) });
    }
}

}

#endif