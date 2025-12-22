#ifndef STACK_H_
#define STACK_H_

#include <cstdint>

/* chip 8 stack */
class Stack
{
    public:
        /* constructors */
        Stack();
        /* pushes a memory address to the stack
           returns true if successful, false if unsuccessful */
        bool push(uint16_t address);
        /* gets the memory address at the top of the stack
           returns a 16-bit address if successful, -1 if unsuccessful */        
        uint16_t pop();
        /* determines if the stack is empty
           returns true if empty, false if not empty */
        bool isEmpty();
        /* the size of the stack */
        uint16_t size;
        
    private:
        /* stack size, contains 16 16-bit addresses */
        static const int MAX_SIZE = 16;
        /* stack implemented as an array */
        uint16_t stack[MAX_SIZE];
};

#endif