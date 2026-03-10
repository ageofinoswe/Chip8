#include "Keypad.h"

// QWERTY       SDL SCANCODE    CHIP8 KEYPAD
// 1 2 3 4      30 31 32 33     1 2 3 C
// Q W E R      20 26 08 21     4 5 6 D
// A S D F      04 22 07 09     7 8 9 E
// Z X C V      29 27 06 25     A 0 B F

// public
Keypad::Keypad()
    : keyboardState{SDL_GetKeyboardState(NULL)}
{       
}

uint8_t Keypad::getKeyboardPress()
{
    if(keyboardState[SDL_SCANCODE_1])
        return 0x1;
    else if(keyboardState[SDL_SCANCODE_2])
        return 0x2;
    else if(keyboardState[SDL_SCANCODE_3])
        return 0x3;
    else if(keyboardState[SDL_SCANCODE_4])
        return 0xC;
    else if(keyboardState[SDL_SCANCODE_Q])
        return 0x4;
    else if(keyboardState[SDL_SCANCODE_W])
        return 0x5;
    else if(keyboardState[SDL_SCANCODE_E])
        return 0x6;
    else if(keyboardState[SDL_SCANCODE_R])
        return 0xD;
    else if(keyboardState[SDL_SCANCODE_A])
        return 0x7;
    else if(keyboardState[SDL_SCANCODE_S])
        return 0x8;
    else if(keyboardState[SDL_SCANCODE_D])
        return 0x9;    
    else if(keyboardState[SDL_SCANCODE_F])
        return 0xE;
    else if(keyboardState[SDL_SCANCODE_Z])
        return 0xA;    
    else if(keyboardState[SDL_SCANCODE_X])
        return 0x0;
    else if(keyboardState[SDL_SCANCODE_C])
        return 0xB;
    else if(keyboardState[SDL_SCANCODE_V])
        return 0xF;
    else
        return 0xFF;
}