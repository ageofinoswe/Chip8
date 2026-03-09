#include "Chip.h"

const int SHIFT_IMPLEMENTATION = 2;
const int JUMP_OFFSET_IMPLEMENTATION = 2;
const int STORE_LOAD_MEMORY_IMPLEMENTATION = 2;


// public
Chip::Chip(string fileName)
    : programCounter{0x200}, indexRegister{}, generalRegisters{}, delayTimer{}, soundTimer{}
{   
    initialize(fileName);
}

void Chip::start()
{
    bool running = true;
    const double frameTime = 1.0 / 700;
    std::cout << frameTime;
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

// 1st nibble - tells you what kind of instruction it is
// 2nd nibble X - used to look up one of the 16 registers (VX) from V0-VF
// 3rd nibble Y - used to look up one of the 16 reigtsers (VY) from V0-VF
// 4th nibble N - a 4 bit number
// NN (3rd and 4th nibble) - an 8 bit immediate number
// NNN (2nd, 3rd, 4th nibble) - a 12 bit immediate memory address
void Chip::decode(const uint16_t opCode)
{
    uint16_t instruction = (opCode >> 12) & 0x000F;
    uint16_t X = (opCode >> 8) & 0x000F;
    uint16_t Y = (opCode >> 4) & 0x000F;
    uint16_t N = opCode & 0x000F;
    uint16_t NN = opCode & 0x00FF;
    uint16_t NNN = opCode & 0x0FFF;
    
    execute(opCode, instruction, X, Y, N, NN, NNN);
}

void Chip::execute(const uint16_t opCode, const uint16_t instruction, const uint16_t X, const uint16_t Y, const uint16_t N, const uint16_t NN, const uint16_t NNN)
{
    switch(instruction)
    {
        case 0x0:
            switch(opCode & 0xF0FF)
            {
                // clear screen
                case 0x00E0:
                {
                    display.clearScreen();
                }
                break;

                // subroutine - return from a subroutine, pop the program counter back
                case 0x00EE:
                {
                    setProgramCounter(stack.pop());
                }
                break;
            }
        break;
        
        // jump - set PC to NNN        
        case 0x1:
        {            
            setProgramCounter(NNN);
        }
        break;

        // subroutine - call a subroutine, push program counter and set PC to NNN
        case 0x2:
        {
            stack.push(programCounter);
            setProgramCounter(NNN);
        }
        break;
        
        // skip conditionally - skip 1 instruction if VX == NN
        case 0x3:
        {
            if(getRegisterValue(X) == NN)
            {
                incrementProgramCounter();
            }
        }
        break;

        // skip conditionally - skip 1 instruction if VX != NN
        case 0x4:
        {
            if(getRegisterValue(X) != NN)
            {
                incrementProgramCounter();
            }
        }
        break;

        // skip conditionally - skip 1 instruction if VX == VY
        case 0x5:
        {
            if(getRegisterValue(X) == getRegisterValue(Y))
            {
                incrementProgramCounter();
            }
        }
        break;

        // set - set register VX to value NN
        case 0x6:
        {
            setRegisterValue(X, NN);
        }
        break;
        
        // add - add NN to VX
        case 0x7:
        {
            uint8_t value = getRegisterValue(X);
            uint8_t newValue = value + (NN);
            setRegisterValue(X, newValue);
        }
        break;

        case 0x8:
            switch(opCode & 0xF00F)
            {   
                // set - VX is set to VY
                case 0x8000:
                {
                    uint8_t VY = getRegisterValue(Y);
                    setRegisterValue(X, VY);
                }
                break;

                // binary or - VX is set to (VX OR VY)
                case 0x8001:
                {
                    uint8_t VxOrVy = getRegisterValue(X) | getRegisterValue(Y);
                    setRegisterValue(X, VxOrVy);
                }
                break;

                // binary and - VX is set to (VX AND VY)
                case 0x8002:
                {
                    uint8_t VxAndVy = getRegisterValue(X) & getRegisterValue(Y);
                    setRegisterValue(X, VxAndVy);
                }
                break;

                // logical xor - VX is set to (VX XOR VY)
                case 0x8003:
                {
                    uint8_t VxXorVy = getRegisterValue(X) ^ getRegisterValue(Y);
                    setRegisterValue(X, VxXorVy);
                }
                break;

                // add - VX = VX + VY, VF is set for overflow
                case 0x8004:
                {
                    uint16_t sum = getRegisterValue(X) + getRegisterValue(Y);
                    setRegisterValue(X, sum & 0xFF);
                    setRegisterValue(0xF, sum > 0xFF);
                }
                break;

                // subtract - VX = VX - VY, VF is set for underflow
                case 0x8005:
                {
                    const uint8_t Vx = getRegisterValue(X);
                    const uint8_t Vy = getRegisterValue(Y);
                    uint8_t difference = Vx - Vy;
                    setRegisterValue(X, difference);
                    if(Vy > Vx)
                    {
                        setRegisterValue(0xF, 0);
                    }
                    else
                    {
                        setRegisterValue(0xF, 1);
                    }
                }
                break;

                // subtrtact - VX = VY - VX, VF is set for underflow
                case 0x8007:
                {
                    const uint8_t Vx = getRegisterValue(X);
                    const uint8_t Vy = getRegisterValue(Y);
                    uint8_t difference = Vy - Vx;
                    setRegisterValue(X, difference);
                    if(Vy < Vx)
                    {
                        setRegisterValue(0xF, 0);
                    }
                    else
                    {
                        setRegisterValue(0xF, 1);
                    }
                }
                break;

                // shift right
                case 0x8006:
                {
                    // IMPLEMENTATION 1 - set VX to VY >> 1, store shifted bit into VF
                    if(SHIFT_IMPLEMENTATION == 1)
                    {
                        uint8_t Vy = getRegisterValue(Y);
                        uint8_t VyShifted = Vy >> 1;
                        uint8_t shiftedBit = Vy & 1;
                        setRegisterValue(X, VyShifted);
                        setRegisterValue(0xF, shiftedBit);
                    }
                    // IMPLEMENTATION 2 - shift VX 1 bit to the right, store shifted bit into VF
                    else if(SHIFT_IMPLEMENTATION == 2)
                    {
                        uint8_t Vx = getRegisterValue(X);
                        uint8_t VxShifted = Vx >> 1;
                        uint8_t shiftedBit = Vx & 1;
                        setRegisterValue(X, VxShifted);
                        setRegisterValue(0xF, shiftedBit);
                    }
                }
                break;

                // shift left
                case 0x800E:
                {
                    // IMPLEMENTATION 1 - set VX to VY << 1, store shifted bit into VF
                    if(SHIFT_IMPLEMENTATION == 1)
                    {
                        uint8_t Vy = getRegisterValue(Y);
                        uint8_t VyShifted = Vy << 1;
                        uint8_t shiftedBit = (Vy >> 7) & 1;
                        setRegisterValue(X, VyShifted);
                        setRegisterValue(0xF, shiftedBit);
                    }
                    // IMPLEMENTATION 2 - shift VX 1 bit to the left, store shifted bit into VF
                    else if(SHIFT_IMPLEMENTATION == 2)
                    {
                        uint8_t Vx = getRegisterValue(X);
                        uint8_t VxShifted = Vx << 1;
                        uint8_t shiftedBit = (Vx >> 7) & 1;
                        setRegisterValue(X, VxShifted);
                        setRegisterValue(0xF, shiftedBit);
                    }
                }
                break;
            }
        break;

        // skip conditionally - skip 1 instruction if VX !== VY
        case 0x9:
        {
            if(getRegisterValue(X) != getRegisterValue(Y))
            {
                incrementProgramCounter();
            }
        }
        break;

        // set index - sets index register I to the value NNN
        case 0xA: 
        {
            setIndexRegister(NNN);
        }
        break;

        // jump with offset
        case 0xB:
        {
            // IMPLEMENTATION 1 - sets program counter to NNN + V0
            if(JUMP_OFFSET_IMPLEMENTATION == 1)
            {
                setProgramCounter(NNN + getRegisterValue(0x0));
            }
            // IMPLEMENTATION 2 - sets program counter to NNN + VX
            else if(JUMP_OFFSET_IMPLEMENTATION == 2)
            {
                setProgramCounter(NNN + getRegisterValue(X));
            }
        }
        break;

        // random - generate a random number and binary AND with NN, put into VX
        case 0xC:
        {
            srand(time(0));
            const uint8_t randNumber = rand() % 0x100; // random number between 0 and 0xFF
            setRegisterValue(X, randNumber & NN);
        }
        break;

        // display & draw - draws left --> right, then up --> down
        case 0xD:
        {
            int x = getRegisterValue(X) % Display::WIDTH; // column
            int y = getRegisterValue(Y) % Display::HEIGHT; // row
            setRegisterValue(0xF, 0);
            for(int row = 0 ; row < N ; row++)
            {
                uint8_t rowData = ram.readMem(indexRegister + row);
                for(int i = 0 ; i < 8 ; i++)
                {
                    int bit = (rowData >> (7 - i)) & 1; // get the most significant bit from the byte
                    if(y < Display::HEIGHT)
                    {
                        if(x < Display::WIDTH)
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
                x = getRegisterValue(X) % Display::WIDTH;
            }
            // draw final sprite
            display.draw();
            SDL_Delay(100);
        }
        break;

        case 0xE:
            switch(opCode & 0xF0FF)
            {
//
                case 0xE09E:
                std::cout << "0xE09E" << std::endl;
                break;
//
                case 0xE0A1:
                std::cout << "0xE0A1" << std::endl;
                break;
            }
        break;

        case 0xF:
            switch(opCode & 0xF0FF)
            {
//
                case 0xF007:
                std::cout << "0xF007" << std::endl;
                break;
//
                case 0xF015:
                std::cout << "0xF015" << std::endl;
                break;
//
                case 0xF018:
                std::cout << "0xF018" << std::endl;
                break;


                // add to index - add to the index register, VX
                case 0xF01E:
                {
                    setIndexRegister(getIndexRegister() + getRegisterValue(X));
                }
                break;
//
                case 0xF00A:
                std::cout << "0xF00A" << std::endl;
                break;

                // font character - sets the index register to the address of the hex character in VX (last nibble)
                case 0xF029:
                {
                    uint8_t fontChar = getRegisterValue(X) & 0x00FF;
                    setIndexRegister(0x50 + (fontChar * 5));
                }
                break;

                // binary coded decimal conversion - store the digits of register VX into index registers I, I+1, I+2
                case 0xF033:
                {
                    uint8_t Vx = getRegisterValue(X);
                    ram.setMem(getIndexRegister(), (Vx / 100) % 10);
                    ram.setMem(getIndexRegister() + 1, (Vx / 10) % 10);
                    ram.setMem(getIndexRegister() + 2, Vx % 10);
                }
                break;

                // store and load memory - store cumulative registers to index registers in succession
                case 0xF055:
                {
                    // IMPLEMENTATION 1 - index register is not incremented
                    if(STORE_LOAD_MEMORY_IMPLEMENTATION == 1)
                    {
                        for(int i = 0 ; i <= X ; i++)
                        {
                            ram.setMem(getIndexRegister() + i, getRegisterValue(i));
                        }
                    }
                    // IMPLEMENTATION 2 - index register is incremented
                    else if(STORE_LOAD_MEMORY_IMPLEMENTATION == 2)
                    {
                        for(int i = 0 ; i <= X ; i++)
                        {
                            ram.setMem(getIndexRegister() + i, getRegisterValue(i));
                        }
                        setIndexRegister(getIndexRegister() + X + 1);
                    }
                }
                break;

                // store and load memory - load cumulative registers from index registers in succession
                case 0xF065:
                {
                    // IMPLEMENTATION 1 - index register is not incremented
                    if(STORE_LOAD_MEMORY_IMPLEMENTATION == 1)
                    {
                        for(int i = 0 ; i <= X ; i++)
                        {
                            setRegisterValue(i, ram.readMem(getIndexRegister() + i));
                        }
                    }
                    // IMPLEMENTATION 2 - index register is incremented
                    else if(STORE_LOAD_MEMORY_IMPLEMENTATION == 2)
                    {
                        for(int i = 0 ; i <= X ; i++)
                        {
                            setRegisterValue(i, ram.readMem(getIndexRegister() + i));
                        }
                        setIndexRegister(getIndexRegister() + X + 1);
                    }                    
                }
                break;

            }
        break;

        default: std::cerr << "Error: Instruction not found!" << std::endl;
        break;
    }
}

void Chip::initialize(const string fileName)
{
    std::ifstream file(fileName, std::ios::binary | std::ios::in);

    int programStart = programCounter;
    char readByte;

    // read the chip8 file and load into ram
    while(file.read(&readByte, 1))
    {
        uint8_t convertByte = static_cast<uint8_t>(readByte);
        ram.setMem(programStart, convertByte);
        programStart += 0x1;
    }

    // set the default fonts
    for(int i = 0 ; i < Font::SIZE ; i++)
    {
        uint16_t start = 0x50;
        const uint8_t* defaultFont = font.getDefaultFont();
        for(int i = 0 ; i < font.SIZE ; i++)
        {
            ram.setMem(start + i, defaultFont[i]);
        }
    }

    // seed the rng
    srand(time(0));
    // output file for debugging purposes    
    ram.memDump();
}

void Chip::currentStateDebug() const
{
    std::cout << "PROGRAM COUNTER: " << "instruction: " << std::hex << programCounter << " powershell: " << programCounter - 0x200 << std::dec <<  std::endl;
    std::cout << "INDEX REGISTER: " << indexRegister << std::endl;
    std::cout << "GENERAL REGISTERS: ";
    for(int i = 0 ; i < 16 ; i++)
        std::cout << "R" << i << ": " << static_cast<int>(generalRegisters[i]) << " ";
    std::cout << std::endl;
}