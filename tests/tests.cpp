#include "../include/cpu.h"
#include <iostream>
#include <vector>
#include <string>

int testRegisterInit(cpu& cpuA);


void runAllTests(cpu& cpuA)
{
    std::cout<<"Init testing"<<std::endl;
    testRegisterInit(cpuA);
}

int testRegisterInit(cpu& cpuA)
{
    std::uint32_t test = cpuA.getRegisterValue(1);
    if (test != 0x0)
    {
        std::cout<<"General purpose register init test FAIL"<<std::endl;
        std::cout<<"Value of register is: "<<std::hex<<test<<std::endl;
    return -1;
    }
    else
    {
        std::cout<<"General purpose register init test PASS"<<std::endl;
        std::cout<<"Register value is: "<<std::hex<<test<<std::endl;
        return 0;
    }
}
        

int main(int argc, char *argv[])
{
    cpu cpuA;
    std::vector<std::string> arguments(argv, argv + argc);

for (std::string arg : arguments)
{
    if (arg == "-all")
    {
        runAllTests(cpuA);        
    }
}
return 0;
}
