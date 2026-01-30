#include "Chip.h"

Chip::Chip(std::string fileName)
{   
    int programStart = 0x200;

    std::ifstream file(fileName, std::ios::binary | std::ios::in);
    char readByte;

    while(file.read(&readByte, 1))
    {
        uint8_t convertByte = static_cast<unsigned char>(readByte);
        ram.setMem(programStart, convertByte);
        programStart += 0x1;
    }
    ram.memDump();
}
