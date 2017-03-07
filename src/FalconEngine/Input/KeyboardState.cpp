#include <FalconEngine/Input/KeyboardState.h>

#include <vector>

namespace FalconEngine
{

KeyboardState::KeyboardState()
{
    // NOTE(Wuxiang): Copy from the Key enum value.
    static std::vector<int> sKeyCode = { 32, 39, 44, 45, 46, 47, 48, 49, 50, 51,
                                         52, 53, 54, 55, 56, 57, 59, 61, 65, 66,
                                         67, 68, 69, 70, 71, 72, 73, 74, 75, 76,
                                         77, 78, 79, 80, 81, 82, 83, 84, 85, 86,
                                         87, 88, 89, 90, 91, 92, 93, 96, 161, 162,
                                         256, 257, 258, 259, 260, 261, 262, 263,
                                         264, 265, 266, 267, 268, 269, 280, 281,
                                         282, 283, 284, 290, 291, 292, 293, 294,
                                         295, 296, 297, 298, 299, 300, 301, 302,
                                         303, 304, 305, 306, 307, 308, 309, 310,
                                         311, 312, 313, 314, 320, 321, 322, 323,
                                         324, 325, 326, 327, 328, 329, 330, 331,
                                         332, 333, 334, 335, 336, 340, 341, 342,
                                         343, 344, 345, 346, 347, 348
                                       };

    for (int i = 0; i < sKeyCode.size(); ++i)
    {
        auto key = Key(sKeyCode[i]);
        insert({ key, KeyState(key) });
    }
}


bool
KeyboardState::KeyDown(Key key) const
{
    return at(key).mDown;
}

bool
KeyboardState::KeyPressed(Key key) const
{
    return at(key).mPressed;
}

bool
KeyboardState::KeyUp(Key key) const
{
    return at(key).mPressed;
}

void
KeyboardState::SetKeyInternal(Key key, bool pressed, double time)
{
    auto keyPressedPrevious = at(key).mPressed;
    auto keyPressedCurrent = pressed;
    auto& keyState = at(key);

    // When just pressed.
    if (keyPressedCurrent && !keyPressedPrevious)
    {
        keyState.mPressed = true;
        keyState.mPressedMoment = time;

        keyState.mDown = true;
        keyState.mUp = false;
    }

    // When just released.
    else if (!keyPressedCurrent && keyPressedPrevious)
    {
        keyState.mPressed = false;
        keyState.mPressedMoment = 0;

        keyState.mDown = false;
        keyState.mUp = true;
    }

    // When still pressed.
    else if (keyPressedCurrent /*&& keyPressedPrevious*/)
    {
        // NOTE(Wuxiang): Need not modify the mPressedMoment.
        keyState.mDown = false;
    }

    // When still released.
    else // (!keyPressedCurrent && !keyPressedPrevious)
    {
        keyState.mUp = false;
    }

}

}
