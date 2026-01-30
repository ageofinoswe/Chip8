#ifndef CHIP_H_
#define CHIP_H_

#include "Font.h"
#include "Ram.h"
#include <fstream>

class Chip
{
    public:
        /* constructors */
        // takes in a file/program name and loads into RAM
        Chip(std::string fileName);
        void start();


    private:
        uint16_t programCounter;
        void incrementProgramCounter();
        void decrementProgramCounter();
        void setProgramCounter(uint16_t address);
        
        uint16_t fetch();
        uint16_t decode();

        uint8_t generalRegisters[16];
        uint8_t getRegisterValue(const int registerNumber) const;
        uint8_t setRegisterValue(const int registerNumber, const uint8_t value);

        Font font;
        Ram ram;
        
};

#endif