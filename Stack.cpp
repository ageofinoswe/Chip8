#include "Stack.h"

Stack::Stack() : stack{}, size(0)
{
}

bool Stack::push(uint16_t address)
{
    if (size < MAX_SIZE)
    {
        stack[size] = address;
        size++;
        return true;
    }
    return false;
}

uint16_t Stack::pop()
{
    if (size > 0)
    {
        size--;
        return stack[size];
    }
    return -1;
}

bool Stack::isEmpty()
{
    return size == 0;
}