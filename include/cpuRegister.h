#pragma once
#include <iostream>
#include "flags.h"

class cpuRegister{
    public:
        cpuRegister(){};
        ~cpuRegister(){};
    protected:
        std::uint8_t getAPSRCurrentCond();
        void setAPSRCondFlags(std::uint32_t flag);
        std::uint32_t getIPSRFlags();
        void initIPSRRegister();

    private:
        typedef struct xPSR{            //program status register
            std::uint32_t APSR;         //application program status register
            std::uint32_t IPSR;         //interrupt program status register
            std::uint32_t EPSR;         //execution program status register
        }xPSR;
        xPSR xPSRRegisters;

};
