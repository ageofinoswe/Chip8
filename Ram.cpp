#include "Ram.h"

Ram::Ram()
    : mainMemory{}
{
}

bool Ram::setMem(const int index, const int value)
{
    if(validateRange(index))
    {
        mainMemory[index] = value;
        return true;
    }
    return false;
}

int Ram::readMem(const int index) const
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