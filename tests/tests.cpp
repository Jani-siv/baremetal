#include "../include/cpu.h"
#include "../include/memory.h"
#include <iostream>
#include <vector>
#include <string>

int testRegisterInit(cpu& cpuA);
int testVectorTableAddressInit(cpu& cpuA);
int testIPSRFlags(cpu& cpuA);
int testCPUID(cpu& cpuA, cpu& cpuB);
int testMemoryWriteAndRead(cpu& cpuA, cpu& cpuB);



void runAllTests(cpu& cpuA, cpu& cpuB)
{
    std::cout<<"Init testing"<<std::endl;
    testRegisterInit(cpuA);
    testVectorTableAddressInit(cpuA);
    testIPSRFlags(cpuA);
    testCPUID(cpuA,cpuB);
    testMemoryWriteAndRead(cpuA, cpuB);
}

int testMemoryWriteAndRead(cpu& cpuA, cpu& cpuB)
{
    bool pass = true;
    std::uint32_t testValue = 0x12345678;
    //write to ROM
    cpuA.writeMemory(0x00000000,testValue);
    //write to SRAM
    cpuA.writeMemory(0x20000000,testValue);
    //write to USBRAM
    cpuA.writeMemory(0x50100400,testValue);
    //test read
        std::uint32_t testing = cpuA.readMemory(0x00000000);
        if (testing != testValue)
        {
        std::cout<<"Memory read from cpuA FAIL"<<std::endl;
        std::cout<<"Value from ROM read is: "<<testing<<std::endl;
        pass = false;
        }
        testing = 0x0;
        testing = cpuB.readMemory(0x00000000);
        if (testing != testValue)
        {
            std::cout<<"Memory read from cpuB FAIL"<<std::endl;
            std::cout<<"Value from ROM read is: "<<testing<<std::endl;
            pass = false; 
        }
        testing = 0x0;
        testing = cpuA.readMemory(0x20000000);
        if (testing != testValue)
        {
            std::cout<<"Memory read from SRAM FAIL"<<std::endl;
            std::cout<<"Value from SRAM read is: "<<testing<<std::endl;
            pass = false;
        }
        testing = 0x0;
        testing = cpuA.readMemory(0x50100400);
        if (testing != testValue)
        {
            std::cout<<"Memory read from USBRAM FAIL"<<std::endl;
            std::cout<<"Value from USBRAM read is: "<<testing<<std::endl;
            pass = false;
        }
if (pass)
{
    std::cout<<"Memory read and write in every memory region with both cpu PASS"<<std::endl;
}
else
{
    std::cout<<"Memory read and write test FAIL"<<std::endl;
}
        return 0;
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
