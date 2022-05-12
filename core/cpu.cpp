#include "../include/cpu.h"

cpu::cpu()
{
    this->CPUID = this->getCPUID();
    //sleep other cores, core 0 init all
    if (this->CPUID == 0x0)
    {
        core::systemMemory::sysMem.initMemory();
    }

    this->TakeReset();
    
}

cpu::~cpu()
{
}
void cpu::runCpu()
{
    std::cout<<"Starting processor"<<std::endl;
    std::cout<<"next instruction write n"<<std::endl;
    std::cout<<"stop processor write q"<<std::endl;
    char userInput[1];
    char *compare = &userInput[0];
    while (strcmp(compare, "q") != 0)
    {
        std::uint16_t data = this->fetchCycle();
        std::cout<<"data from memoty: "<<std::hex<<static_cast<int>(data)<<std::endl;
        this->decodeCycle(data);
        std::cout<<"General purpose registers:"<<std::endl;
        this->printRegistersValues();
        std::cout<<"stop processor write q"<<std::endl;

        std::cin >> compare;
    }
}

void cpu::printRegistersValues()
{
    int i = 0;
    for (auto& value : this->GPregisters)
    {
        std::cout<<std::dec<<"R"<<i<<" Value: ";
        std::cout<<std::hex<<static_cast<int>(value)<<std::endl;
        i++;
    }
}

std::uint16_t cpu::fetchCycle()
{
    std::uint32_t address = this->_PC[0];
    std::cout<<"address: "<<std::hex<<static_cast<int>(address)<<std::endl;
    std::cout<<"PC* "<<std::hex<<static_cast<int>(this->_PC[0])<<std::endl;
    this->setNextInstructionAddress();
    std::uint16_t data = this->readMemory(address);
    return data;
}

void cpu::decodeCycle(std::uint16_t data)
{
    std::uint16_t decodedValue = decodeOP(data);
    std::uint8_t imm5 = 0x0;
    std::uint8_t imm8 = 0x0;
    std::uint8_t Rm=0x0, Rd=0x0;
    std::cout<<"imm5: "<<std::hex<<static_cast<int>(imm5)<<std::endl;
    switch(decodedValue)
    {
        case LSLS:
             {
                 Rd = data & 0x7;
                 Rm = data >> 3 & 0x7;
                 std::cout<<std::hex<<"Rd: "<<static_cast<int>(Rd)<<" Rm: "<<static_cast<int>(Rm)<<std::endl;
                 imm5 = getImm5(data);
                 std::cout<<"LSLS"<<std::endl;
                 if (imm5 == 0x0)
                 {
                     //MOV register
                     if (Rd == 0xF)
                     {
                        this->_PC[0] = Rm;
                     }
                     else
                     {
                        this->GPregisters[Rd] = Rd;
                     }
                 }
                 //rd (destination) = rm shift bytes imm5 left
                 this->GPregisters[Rd] = this->GPregisters[Rm] << imm5;
                 std::cout<<std::hex<<"Result: "<<static_cast<int>(this->GPregisters[Rd])<<std::endl;
                 break;
             }
        case MOVS:
             {
                 Rd = (data >> 8 & 0x7);
                 imm8 = getImm8(data);
                 this->GPregisters[Rd] = imm8;
                 std::cout<<"MOVS: "<<static_cast<int>(this->GPregisters[Rd])<<std::endl;
                 break;
             }
        case STR:
             {
                 std::cout<<"STR"<<std::endl;
                 break;
             }
        case PUSH:
             {
                 std::cout<<"PUSH"<<std::endl;
                 break;
             }
        case BL:
             {
                 std::cout<<"BL"<<std::endl;
                 break;
             }
        default:
             {
                 std::cout<<"Unknow command"<<std::endl;
                 break;
             }
    }

}

void cpu::setNextInstructionAddress()
{
    this->GPregisters[15] += 4;
}

void cpu::writeMemory(std::uint32_t address, const std::uint16_t &value)
{
    core::systemMemory::sysMem.writeMemory(address,value);
}

void cpu::writeMemory32(std::uint32_t address, const std::uint32_t &value)
{
    core::systemMemory::sysMem.writeMemory32(address, value);
}

std::uint16_t cpu::readMemory(std::uint32_t address)
{
    std::uint16_t dataFromMemory = core::systemMemory::sysMem.readMemory(address);
    return dataFromMemory;
}

std::uint32_t cpu::readMemory32(std::uint32_t address)
{
    std::uint32_t data = core::systemMemory::sysMem.readMemory32(address);
    return data;
}

short cpu::getCPUid()
{
    return this->CPUID;
}
short cpu::getCPUID()
{
    return core::systemMemory::sysMem.getCPUID();
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
    this->initIPSRRegister();
    //for (int i = 0; i < 6; i++)
    //{
    //    this->xPSRRegisters.IPSR &= ~(1UL << i);
    //}
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
