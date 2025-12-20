#ifndef CHIP_H_
#define CHIP_H_

#include "Font.h"
#include "Ram.h"

class Chip
{
    public:    
        Chip();

    private:
        Font font;
        Ram ram;
};

#endif