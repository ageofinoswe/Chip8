#include <iostream>
#include "Ram.cpp"

int main()
{
    Ram x;
    std::cout << "----------------------------------" << std::endl;
    std::cout << x.readMem(0) << std::endl;
    std::cout << x.readMem(4095) << std::endl;
    std::cout << x.readMem(-1) << std::endl;
    std::cout << x.readMem(4096) << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cout << x.setMem(0, 5) << std::endl;
    std::cout << x.setMem(4095, 10) << std::endl;
    std::cout << x.setMem(-1, 15) << std::endl;
    std::cout << x.setMem(4096, 20) << std::endl;    
    std::cout << "----------------------------------" << std::endl;
    std::cout << x.readMem(0) << std::endl;
    std::cout << x.readMem(4095) << std::endl;
    std::cout << x.readMem(-1) << std::endl;
    std::cout << x.readMem(4096) << std::endl;
}
