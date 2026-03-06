#ifndef STACK_H_
#define STACK_H_

#include <cstdint>

class Stack
{
    public:
        // constructors 
        Stack();
        // pushes a memory address to the stack
        void push(uint16_t address);
        // gets the memory address at the top of the stack      
        uint16_t pop();
        // determines if the stack is empty
        bool isEmpty() const;
        // the size of the stack
        int size;
        
    private:
        // max stack size, contains 16 16-bit addresses
        static constexpr int MAX_SIZE = 16;
        // stack representation
        uint16_t stack[MAX_SIZE];
};

#endif