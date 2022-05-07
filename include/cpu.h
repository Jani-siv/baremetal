#pragma once
//26 interrupts
#define VECTORTABLEMAX 0xFFFFFF80
#define THREADMODE false
#define HANDLERMODE true
#define ROMSIZE 16000
#include <iostream>
#include "../include/memory.h"
#include "../include/decoder.h"
#include "../include/opcodes.h"

class cpu : public decoder {
    public:
        cpu(core::memory* mainMemory);
        ~cpu();
        short getCPUid();
        std::uint32_t getRegisterValue(unsigned int num);
        std::uint32_t getVectorTableStartAddress();
        std::uint32_t getIPSRFlags();
        void writeMemory(std::uint32_t address, const std::uint16_t &value);
        void writeMemory32(std::uint32_t address, const std::uint32_t &value);
        std::uint16_t readMemory(std::uint32_t address);
        std::uint32_t readMemory32(std::uint32_t address);
        void runCpu();

    private:
        short CPUID;
        short getCPUID();
        std::uint32_t fetchCycle();
        void decodeCycle(std::uint32_t data);
        void executeCycle();
        void * checkInterrputsRegisters();
        void * checkXIPRegisters();
        void setNextInstructionAddress();
        std::uint32_t GPregisters[16];  //ARM core registers
        std::uint32_t * MSP = nullptr;
        std::uint32_t * PSP = nullptr;
        std::uint32_t * LR = &GPregisters[14];   //contain return address from subroutine
        std::uint32_t * _PC = &GPregisters[15];
        std::uint32_t StatusRegisters;
        std::uint32_t PRIMASK;       //prioritization scheme for exeptions and interrupts
        std::uint32_t CONTROL;       //identified current stack
        typedef struct xPSR{            //program status register
            std::uint32_t APSR;         //application program status register
            std::uint32_t IPSR;         //interrupt program status register
            std::uint32_t EPSR;         //execution program status register
        }xPSR;
        xPSR xPSRRegisters;
        uint32_t VTOR;                  //vectortable offset
        uint32_t vectortable;
        bool processorMode;
        core::memory *ptr = nullptr;
        void printRegistersValues(); 


        void TakeReset();
};
