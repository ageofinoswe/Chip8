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
        uint16_t fetch();

    private:
        uint16_t programCounter;
        void incrementProgramCounter();
        void decrementProgramCounter();
        void setProgramCounter(uint16_t address);
        Font font;
        Ram ram;
        
};

#endif