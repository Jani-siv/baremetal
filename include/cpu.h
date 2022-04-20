#pragma once
#define VECTORTABLEMAX 0xFFFFFF80
#define THREADMODE false
#define HANDLERMODE true
#include <iostream>

class cpu {
    public:
        cpu();
        ~cpu();
        std::uint32_t getRegisterValue(unsigned int num);
        std::uint32_t getVectorTableStartAddress();
        std::uint32_t getIPSRFlags();

    private:
        std::uint32_t GPregisters[16];  //ARM core registers
        std::uint32_t * const MSP = &GPregisters[13];
        std::uint32_t * PSP = nullptr;
        std::uint32_t * const _LR = &GPregisters[14];   //contain return address from subroutine
        std::uint32_t * const _PC = &GPregisters[15];
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
        


        void TakeReset();
};
