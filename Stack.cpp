#include "Stack.h"

//public
Stack::Stack() : stack{}, size(0)
{
}

void Stack::push(uint16_t address)
{
    if (size < MAX_SIZE)
    {
        stack[size] = address;
        size++;
    }
}

uint16_t Stack::pop()
{
    if (size > 0)
    {
        uint16_t top = stack[size];
        size--;
        return top;
    }
    return -1;
}

bool Stack::isEmpty() const
{
    return size == 0;
}