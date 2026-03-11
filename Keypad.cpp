#include "Keypad.h"

// QWERTY       SDL SCANCODE    CHIP8 KEYPAD
// 1 2 3 4      30 31 32 33     1 2 3 C
// Q W E R      20 26 08 21     4 5 6 D
// A S D F      04 22 07 09     7 8 9 E
// Z X C V      29 27 06 25     A 0 B F

// public
Keypad::Keypad()
    : keyboard{SDL_GetKeyboardState(NULL)}, keyboardState{}
{       
    scanCodes[0] = SDL_SCANCODE_1;
    scanCodes[1] = SDL_SCANCODE_2;
    scanCodes[2] = SDL_SCANCODE_3;
    scanCodes[3] = SDL_SCANCODE_4;
    scanCodes[4] = SDL_SCANCODE_Q;
    scanCodes[5] = SDL_SCANCODE_W;
    scanCodes[6] = SDL_SCANCODE_E;
    scanCodes[7] = SDL_SCANCODE_R;
    scanCodes[8] = SDL_SCANCODE_A;
    scanCodes[9] = SDL_SCANCODE_S;
    scanCodes[10] = SDL_SCANCODE_D;
    scanCodes[11] = SDL_SCANCODE_F;
    scanCodes[12] = SDL_SCANCODE_Z;
    scanCodes[13] = SDL_SCANCODE_X;
    scanCodes[14] = SDL_SCANCODE_C;
    scanCodes[15] = SDL_SCANCODE_V;
}

const bool Keypad::checkKeyPress(const int chipKey)
{
    SDL_PumpEvents();
    const bool* kbState = getKeyboardState();
    switch(chipKey)
    {
        case 0x1: return kbState[0];
        case 0x2: return kbState[1];
        case 0x3: return kbState[2];
        case 0xC: return kbState[3];

        case 0x4: return kbState[4];
        case 0x5: return kbState[5];
        case 0x6: return kbState[6];
        case 0xD: return kbState[7];

        case 0x7: return kbState[8];
        case 0x8: return kbState[9];
        case 0x9: return kbState[10];
        case 0xE: return kbState[11];

        case 0xA: return kbState[12];
        case 0x0: return kbState[13];
        case 0xB: return kbState[14];
        case 0xF: return kbState[15];
        default: return false;
    }
    return false;
}

const uint8_t Keypad::getKeyPress()
{
    const bool* kbState = getKeyboardState();
    for(int key = 0 ; key < SIZE ; key++)
    {
        if(kbState[key])
        {
            switch(key)
            {
                case 0: return 0x1;
                case 1: return 0x2;
                case 2: return 0x3;
                case 3: return 0xC;

                case 4: return 0x4;
                case 5: return 0x5;
                case 6: return 0x6;
                case 7: return 0xD;

                case 8: return 0x7;
                case 9: return 0x8;
                case 10: return 0x9;
                case 11: return 0xE;
                
                case 12: return 0xA;
                case 13: return 0x0;
                case 14: return 0xB;
                case 15: return 0xF;
                default: return 0xFF;
            }
            return 0xFF;
        }
    }
    return 0xFF;
}

// private
const bool* Keypad::getKeyboardState()
{
    for(int i = 0 ; i < SIZE ; i++)
    {
        keyboardState[i] = keyboard[scanCodes[i]];
    }
    return keyboardState;
}