#include "../include/cpu.h"

cpu::cpu()
{
    this->TakeReset();
}

cpu::~cpu()
{
}

std::uint32_t cpu::getIPSRFlags()
{
    return this->xPSRRegisters.IPSR;
}

std::uint32_t cpu::getRegisterValue(unsigned int num)
{
    if (num <16)
        return this->GPregisters[num];
    else return -1;
}

std::uint32_t cpu::getVectorTableStartAddress()
{
    return this->vectortable;
}


void cpu::TakeReset()
{
    for (int i = 0; i < 16; i++)
    {
        this->GPregisters[i] = 0x0;
    }
    
    //vector table offset
    this->VTOR = 0x0;
    //set vector table start address with mask
    this->vectortable = this->VTOR & 0xFFFFFF80;

    //set processor mode
    this->processorMode = THREADMODE;
    
    //LR value from usersoftware

    //IPSR<5:0> = zeros
    for (int i = 0; i < 6; i++)
    {
        this->xPSRRegisters.IPSR &= ~(1UL << i);
    }
/*
LR = bits(32) UNKNOWN;
// Value must be initialised by software
APSR = bits(32) UNKNOWN;
// Flags UNPREDICTABLE from reset
IPSR<5:0> = Zeros(6);
// Exception number cleared at reset
PRIMASK.PM = ‘0’;
// Priority mask cleared at reset
CONTROL.SPSEL = ‘0’;
// Current stack is Main
CONTROL.nPRIV = ‘0’;
// Thread is privileged
ResetSCSRegs();
// Catch-all function for System Control Space reset
for i = 0 to 511
// All exceptions Inactive
ExceptionActive[i] = ‘0’;
ClearEventRegister();
// See WFE instruction for more information
SP_main = MemA[vectortable,4] AND 0xFFFFFFFC<31:0>;
SP_process = ((bits(30) UNKNOWN):’00’);
start = MemA[vectortable+4,4];
// Load address of reset routine
BLXWritePC(start);
*/
}
