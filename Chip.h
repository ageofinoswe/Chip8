#ifndef CHIP_H_
#define CHIP_H_

#include "Font.h"
#include "Ram.h"
#include <fstream>

class Chip
{
    public:
        Chip(std::string fileName);

    private:
        uint16_t programCounter;
        Font font;
        Ram ram;

};

#endif