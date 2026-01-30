#include "Chip.h"

Chip::Chip(std::string fileName)
    : programCounter{0x200}
{   
    int programStart = programCounter;

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

void Chip::start()
{
    return;
}


void Chip::incrementProgramCounter()
{
    programCounter += 0x2;
}

void Chip::decrementProgramCounter()
{
    programCounter -= 0x2;
}

void Chip::setProgramCounter(uint16_t address)
{
    programCounter = 0xfff & address;
}

uint16_t Chip::fetch()
{
    uint16_t msb = ram.readMem(programCounter) << 8;
    uint16_t lsb = ram.readMem(programCounter + 0x1);
    incrementProgramCounter();
    return msb | lsb;
}
