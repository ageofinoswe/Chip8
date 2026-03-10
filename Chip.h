#ifndef CHIP_H_
#define CHIP_H_

#include <fstream>
#include <string>
#include <cstdint>
#include <chrono>
#include "Font.h"
#include "Ram.h"
#include "Display.h"
#include "Stack.h"
#include "Keypad.h"

using std::string;

class Chip
{
    public:
        // constructor - takes in a chip8 file
        Chip(string fileName);
        // constructor - takes in a chip8 file and opcode configs
        Chip(string fileName, const int SHIFT_IMPLEMENTATION, const int JUMP_OFFSET_IMPLEMENTATION, const int STORE_LOAD_MEMORY_IMPLEMENTATION);
        // starts the chip8 emulation
        void start();

    private:
        // program counter points to current instruction in memory (12 bits used)
        uint16_t programCounter;
        // increments the program counter by 2 bytes
        void incrementProgramCounter();
        // decrements the program counter by 2 bytes
        void decrementProgramCounter();
        // set the program counter to a specific address in memory
        void setProgramCounter(const uint16_t address);

        // index register that point to a specific address in memory (12 bits used)
        uint16_t indexRegister;
        // gets the current address that the index register is pointing to
        uint16_t getIndexRegister() const;
        // sets the index register to a specific address in memory
        void setIndexRegister(const uint16_t newIndexRegister);

        // 16 general purpose registers (8 bits)
        uint8_t generalRegisters[16];
        // gets the value at a specific register
        uint8_t getRegisterValue(const uint8_t registerNumber) const;
        // sets a value at a specific register
        void setRegisterValue(const uint8_t registerNumber, const uint8_t value);

        // 1 fetch, 1 decode, 1 execute instruction
        void cycle();
        // fetches the current instruction in memory that the program counter points to
        uint16_t fetch();
        // decodes the instruction and sends it to the execute instruction
        void decode(const uint16_t opCode);
        // executes the current opcode
        void execute(const uint16_t opCode, const uint16_t instruction, const uint16_t X, const uint16_t Y, const uint16_t N, const uint16_t NN, const uint16_t NNN);

        // initialize the chip
        void initialize(const string fileName);

        // fonts
        Font font;
        // 4kB RAM
        Ram ram;
        // stack for subroutine calls
        Stack stack;
        // 64x32 display
        Display display;
        // keypad
        Keypad keypad;

        // delay timer, sound timer,  60Hz
        uint8_t delayTimer;
        uint8_t soundTimer;

        // opcode implementations, configurable
        int SHIFT_IMPLEMENTATION;
        int JUMP_OFFSET_IMPLEMENTATION;
        int STORE_LOAD_MEMORY_IMPLEMENTATION;

        // used for debugging purposes
        void currentStateDebug() const;
};

#endif