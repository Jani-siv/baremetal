#include "../include/cpu.h"
#include "../include/memory.h"
#include <iostream>
#include <vector>
#include <string>

int testRegisterInit(cpu& cpuA);
int testVectorTableAddressInit(cpu& cpuA);
int testIPSRFlags(cpu& cpuA);
int testCPUID(cpu& cpuA, cpu& cpuB);


void runAllTests(cpu& cpuA, cpu& cpuB)
{
    std::cout<<"Init testing"<<std::endl;
    testRegisterInit(cpuA);
    testVectorTableAddressInit(cpuA);
    testIPSRFlags(cpuA);
    testCPUID(cpuA,cpuB);
}

int testCPUID(cpu& cpuA, cpu& cpuB)
{
    short first = cpuA.getCPUid();
    if (first == 0)
    {
        std::cout<<"Test of first cpuID PASS: "<<first<<std::endl;
        first = cpuB.getCPUid();
        if ((first & 0x1) == 1)
        {
            std::cout<<"Test of second cpuID PASS: "<<first<<std::endl;
        }
        else
        {
            std::cout<<"Test of second cpuID FAIL: "<<first<<std::endl;
            return -1;
        }
    }
    else
    {
        std::cout<<"Test of first cpuID FAIL: "<<first<<std::endl;
        return -1;
    }
return 0;
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
    memory mainMemory;
    memory *ptr = &mainMemory;
    cpu cpuA(ptr);
    cpu cpuB(ptr);
    std::vector<std::string> arguments(argv, argv + argc);

for (std::string arg : arguments)
{
    if (arg == "-all")
    {
        runAllTests(cpuA, cpuB);        
    }
}
return 0;
}
