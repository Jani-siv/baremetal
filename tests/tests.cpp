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
    bool passTests = true;
    if (testRegisterInit(cpuA) < 0) exit(-1);
    if (testVectorTableAddressInit(cpuA) < 0) exit(-1);
    if (testCPUID(cpuA,cpuB) < 0) exit(-1);
    if (testMemoryWriteAndRead(cpuA, cpuB) < 0) exit(-1);
    std::cout<<"Do you want run cpu? y/n:"<<std::endl;
    char temp[1];
    char *answer = temp;
    std::cin >> answer;
    if (answer[0] == 'y')
    {
    //set test data to test assembly
    cpuA.writeMemory(0x00000000, 0x016B);
    cpuA.writeMemory(0x00000004, 0x2019);
    cpuA.writeMemory(0x00000008, 0x625A);
    cpuA.writeMemory(0x0000000C, 0xB000);
    cpuA.writeMemory(0x00000010, 0xF000);
    cpuA.runCpu();
    }
}

int testMemoryWriteAndRead(cpu& cpuA, cpu& cpuB)
{
    bool pass = true;
    std::uint16_t testValue = 0x4141;
    std::uint32_t testValue32 = 0x41414141;
    //write to ROM
    cpuA.writeMemory(0x00000000,testValue);
    //write to SRAM
    cpuA.writeMemory(0x20000000,testValue);
    //write to USBRAM
    cpuA.writeMemory(0x50100400,testValue);
    //test read
    cpuA.writeMemory32(0x00000020, testValue32);

        std::uint32_t testing32 = cpuA.readMemory32(0x00000020);
        if (testing32 != testValue32)
        {
            std::cout<<"Memory read 32 bus FAIL"<<std::endl;
            std::cout<<"Value from 32 bus: "<<testing32<<std::endl;
            pass = false;     
        }
        std::uint16_t testing = cpuA.readMemory(0x00000000);
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

int main(int argc, char *argv[])
{
    std::cout<<"Start testing"<<std::endl;
    core::systemMemory::sysMem.initMemory();
    cpu cpuA;
    cpu cpuB;
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
