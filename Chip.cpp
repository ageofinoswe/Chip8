#include "Chip.h"

// public
Chip::Chip(string fileName)
    : programCounter{0x200}, indexRegister{}, generalRegisters{}
{   
    initialize(fileName);
}

void Chip::start()
{
    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        cycle();
    }
    display.destroyWindow();
}

// private
void Chip::incrementProgramCounter()
{
    programCounter += 2;
}
void Chip::decrementProgramCounter()
{
    programCounter -= 2;
}
void Chip::setProgramCounter(const uint16_t address)
{
    programCounter = 0x0FFF & address;
}

uint16_t Chip::getIndexRegister() const
{
    return indexRegister;
}
void Chip::setIndexRegister(const uint16_t newIndexRegister)
{
    indexRegister = 0x0FFF & newIndexRegister;
}

uint8_t Chip::getRegisterValue(const uint8_t registerNumber) const
{
    if(registerNumber >= 0 && registerNumber < 16)
    {
        return generalRegisters[registerNumber];
    }
    return -1;
}
void Chip::setRegisterValue(const uint8_t registerNumber, const uint8_t value)
{
    if(registerNumber >= 0 && registerNumber < 16)
    {
        generalRegisters[registerNumber] = value;
    }
}

void Chip::cycle()
{
    uint16_t opcode = fetch();
    decode(opcode);
}

uint16_t Chip::fetch()
{
    uint16_t msb = ram.readMem(programCounter) << 8;
    uint16_t lsb = ram.readMem(programCounter + 1);
    incrementProgramCounter();
    return msb | lsb;
}

void Chip::decode(const uint16_t opCode)
{
    uint16_t nibbleOne = (0xF000 & opCode) >> 12;
    uint16_t nibbleTwo = (0x0F00 & opCode) >> 8;
    uint16_t nibbleThree = (0x00F0 & opCode) >> 4;
    uint16_t nibbleFour = (0x000F & opCode);

    execute(nibbleOne, nibbleTwo, nibbleThree, nibbleFour);
}

// 1st nibble - tells you what kind of instruction it is
// 2nd nibble X - used to look up one of the 16 registers (VX) from V0-VF
// 3rd nibble Y - used to look up one of the 16 reigtsers (VY) from V0-VF
// 4th nibble N - a 4 bit number
// NN (3rd and 4th nibble) - an 8 bit immediate number
// NNN (2nd, 3rd, 4th nibble) - a 12 bit immediate memory address
void Chip::execute(const uint16_t nibbleOne, const uint16_t nibbleTwo, const uint16_t nibbleThree, const uint16_t nibbleFour)
{
    switch(nibbleOne){
        // CLEAR SCREEN
        case 0x0:
            display.clearScreen();
        break;
        
        // JUMP - set PC to NNN
        case 0x1:
            setProgramCounter(nibbleTwo << 8  | nibbleThree << 4 | nibbleFour);
        break;
        
        // SET - set register VX to value NN
        case 0x6:
            setRegisterValue(nibbleTwo, nibbleThree << 4 | nibbleFour);
        break;
        
        // ADD - add NN to VX
        case 0x7:
        {
            uint8_t value = getRegisterValue(nibbleTwo);
            uint8_t newValue = value + (nibbleThree << 4 | nibbleFour);
            setRegisterValue(nibbleTwo, newValue);
        }
        break;

        // SET INDEX - sets index register I to the value NNN
        case 0xA: 
            setIndexRegister(nibbleTwo << 8 | nibbleThree << 4 | nibbleFour);
        break;

        // DISPLAY & DRAW
        // draws left --> right, then up --> down
        case 0xD:
        {
            // get column and row coordinates
            int x = getRegisterValue(nibbleTwo) % Display::WIDTH; // column
            int y = getRegisterValue(nibbleThree) % Display::HEIGHT; // row
            setRegisterValue(0xF, 0);

            for(int row = 0 ; row < nibbleFour ; row++)
            {
                uint8_t rowData = ram.readMem(indexRegister + row);
                for(int i = 0 ; i < 8 ; i++)
                {
                    int bit = (rowData >> (7 - i)) & 1; // get the most significant bit from the byte
                    if(y < Display::HEIGHT)
                    {
                        if(x + i < Display::WIDTH)
                        {
                            if(display.isOn(x, y) && bit)
                            {
                                display.setPixel(x, y, false);
                                setRegisterValue(0xF, 1);
                            }
                            else if(bit)
                            {
                                display.setPixel(x, y, true);
                            }
                        }
                    }
                    x++; // go to next pixel in sprite column
                }
                // move down to next row and reset column coordinate
                y++;
                x = getRegisterValue(nibbleTwo) % Display::WIDTH;
            }
            // draw final sprite
            display.draw();
        }
        break;
    }
}

void Chip::initialize(const string fileName)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::in);

    int programStart = programCounter;
    char readByte;

    while(file.read(&readByte, 1))
    {
        uint8_t convertByte = static_cast<uint8_t>(readByte);
        ram.setMem(programStart, convertByte);
        programStart += 0x1;
    }
    
    ram.memDump();
}

void Chip::currentStateDebug() const
{
    std::cout << "PROGRAM COUNTER: " << programCounter << std::endl;
    std::cout << "INDEX REGISTER: " << indexRegister << std::endl;
    std::cout << "GENERAL REGISTERS: ";
    for(int i = 0 ; i < 16 ; i++)
        std::cout << "R" << i << ": " << static_cast<int>(generalRegisters[i]) << " ";
    std::cout << std::endl;
}