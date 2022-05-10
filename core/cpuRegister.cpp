#include "../include/cpuRegister.h"

std::uint8_t cpuRegister::getAPSRCurrentCond()
{
    std::uint8_t cond = (this->xPSRRegisters.APSR & 0x0000000F);
    return cond;
}

void cpuRegister::setAPSRCondFlags(std::uint32_t flag)
{
    SETFLAG(this->xPSRRegisters.APSR, flag);
}
std::uint32_t cpuRegister::getIPSRFlags()
{
    return this->xPSRRegisters.IPSR;
}

void cpuRegister::initIPSRRegister()
{
        for (int i = 0; i < 6; i++)
    {
        this->xPSRRegisters.IPSR &= ~(1UL << i);
    }
}

