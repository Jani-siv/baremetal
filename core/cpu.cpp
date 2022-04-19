#include "../include/cpu.h"

cpu::cpu()
{
    this->TakeReset();
}

cpu::~cpu()
{
}

void cpu::TakeReset()
{
    for (auto i : this->GPregisters)
        i = 0x0;

/*
    VTOR = Zeros(32); //vector_table
for i = 0 to 12
R[i] = bits(32) UNKNOWN;
bits(32) vectortable = VTOR;
CurrentMode = Mode_Thread;
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
