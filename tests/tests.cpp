#include "../include/cpu.h"
#include <iostream>
#include <vector>
#include <string>

int testRegisterInit(cpu& cpuA);
int testVectorTableAddressInit(cpu& cpuA);
int testIPSRFlags(cpu& cpuA);

void runAllTests(cpu& cpuA)
{
    std::cout<<"Init testing"<<std::endl;
    testRegisterInit(cpuA);
    testVectorTableAddressInit(cpuA);
    testIPSRFlags(cpuA);
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
        
int testVectorTableAddressInit(cpu& cpuA)
{
    std::uint32_t test = cpuA.getVectorTableStartAddress();
    if (test != 0x0)
    {
        std::cout<<"Vector table init FAIL"<<std::endl;
        std::cout<<"Vector table start address is: "<<test<<std::endl;
        return -1;
    }
    else
    {
        std::cout<<"Vector table init PASS"<<std::endl;
        std::cout<<"Vector table start address is: "<<test<<std::endl;
        return 0;
    }
}

int testIPSRFlags(cpu& cpuA)
{
    std::uint32_t test = cpuA.getIPSRFlags();
    if ((test & 0x1F) > 0x00)
    {
        std::cout<<"IPSRFlags init FAIL"<<std::endl;
        std::cout<<"IPSRFlags value: "<<std::hex<<(test & 0x1F)<<std::endl;
    return -1;
    }
    else
    {
        std::cout<<"IPSRFlags init PASS"<<std::endl;
        std::cout<<"IPSRFlags value: "<<std::hex<<(test & 0x1F)<<std::endl;
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
