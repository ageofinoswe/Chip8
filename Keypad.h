#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <SDL3/SDL.h>

// QWERTY       SDL SCANCODE    CHIP8 KEYPAD
// 1 2 3 4      30 31 32 33     1 2 3 C
// Q W E R      20 26 08 21     4 5 6 D
// A S D F      04 22 07 09     7 8 9 E
// Z X C V      29 27 06 25     A 0 B F

class Keypad
{
    public:
        // constructor
        Keypad();
        // gets the chip8 keyboard value that was pressed
        uint8_t getKeyboardPress();
    private:
        // stores the SDL keyboard state
        const bool* keyboardState;
};

#endif