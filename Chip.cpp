#include "Chip.h"

Chip::Chip(std::string fileName)
    : programCounter{0x200}, generalRegisters{}
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

void Chip::decode(const uint16_t opCode)
{
    execute((0xF000 & opCode) >> 12, (0x0F00 & opCode) >> 8, (0x00F0 & opCode) >> 4, (0x000F & opCode));
}

void Chip::execute(const uint8_t nibbleOne, const uint8_t nibbleTwo, const uint8_t nibbleThree, const uint8_t nibbleFour)
{
    switch(nibbleThree){
        case 0: std::cout << "0";
        break;
        case 0xe: std::cout << "e";
        break;
    }
}


uint8_t Chip::getRegisterValue(const int registerNumber) const
{
    if(registerNumber >= 0 && (registerNumber < sizeof(generalRegisters) / sizeof(generalRegisters[0])))
    {
        return generalRegisters[registerNumber];
    }

    return -1;
}

uint8_t Chip::setRegisterValue(const int registerNumber, const uint8_t value)
{
    if(registerNumber >= 0 && (registerNumber < sizeof(generalRegisters) / sizeof(generalRegisters[0])))
    {
        generalRegisters[registerNumber] = value;
        return value;
    }
    
    return -1;
}