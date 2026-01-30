#include "Ram.h"

Ram::Ram()
    :   mainMemory{}
{
}

bool Ram::setMem(const int index, const uint8_t value)
{
    if(validateRange(index))
    {
        mainMemory[index] = value;
        return true;
    }
    return false;
}

uint8_t Ram::readMem(const int index) const
{
    if(validateRange(index))
    {
        return mainMemory[index];
    }
    return -1;
}

bool Ram::validateRange(const int index) const
{
    return (index >= 0 && index < MEMORY_SIZE);
}

void Ram::memDump() const
{
    std::ofstream output;
    output.open("memDump.txt");
    if(output.is_open())
    {
        for(int i = 0 ; i < MEMORY_SIZE ; i++)
        {
            output << std::dec << "Address " << i << ":\t\t" << std::hex << static_cast<int>(mainMemory[i]) << std::endl;
        }
        output.close();
    }
}