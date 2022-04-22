#include "../include/memory.h"

memory::memory()
{
 this->initSIO();
}
memory::~memory()
{
}
std::uint16_t memory::readMemory(std::uint32_t address)
{
    std::uint16_t data = 0x0;
    if (address < SRAMBASE)
    {
        for (int i=0; i < 2; i++)
        {
            data = (data << 8);
            data += this->ROM[address+i];
        }
            return data;
        
    }
    else if (address >= SRAMBASE && address < USBRAMBASE)
    {
        address -= SRAMBASE;
        for (int i=0; i < 2; i++)
        {
            data = (data << 8);
            data += this->SRAM[address+i];
        }
        return data;
    }
    else if (address >= USBRAMBASE)
    {
        address -= USBRAMBASE;
        for (int i=0; i < 2; i++)
        {
            data = (data << 8);
            data += this->USBRAM[address+i];
        }
        return data;
    }
    std::cout<<"Memory error"<<std::endl;
return 0x0;
}
void memory::writeMemory(std::uint32_t address,const std::uint16_t &value)
{
    if (address < SRAMBASE)
    {
        this->writeRom(address, value);
    }
    else if (address >= SRAMBASE && address < USBRAMBASE)
    {
        this->writeSram(address, value);
    }
    else if (address >= USBRAMBASE)
    {
        this->writeUsbram(address, value);
    }

}

void memory::writeRom(const std::uint32_t address,const std::uint16_t &value)
{
    std::uint16_t mask = 0x00FF;
    for (int i = 0; i < 2; i++)
    {
        char convertedValue[1];
        convertedValue[0] = (value & mask) >> (8*i);
        std::memcpy(&this->ROM[(address+(1-i))],&convertedValue[0],sizeof(char));
        mask = (mask << 8);
    }
}

void memory::writeSram(std::uint32_t address,const std::uint16_t &value)
{
   address -= SRAMBASE;
    std::uint32_t mask = 0x00FF;
    for (int i = 0; i < 2; i++)
    {   
        char convertedValue[1];
        convertedValue[0] = (value & mask) >> (8*i);
        std::memcpy(&this->SRAM[(address+(1-i))],&convertedValue[0],sizeof(char));
        mask = (mask << 8);
    }
}

void memory::writeUsbram(std::uint32_t address,const std::uint16_t &value)
{
    address -= USBRAMBASE;
    std::uint32_t mask = 0x00FF;
    for (int i = 0; i < 2; i++)
    {
        char convertedValue[1];
        convertedValue[0] = (value & mask) >> (8*i);
        std::memcpy(&this->USBRAM[(address+(1-i))],&convertedValue[0],sizeof(char));
        mask = (mask << 8);
    }
}

void memory::initMemory()
{
    for (int i = 0; i < ROMSIZE; i++)
    {
      this->ROM[i] = 0x0;
    }
    for (int i = 0; i < SRAMSIZE; i++)
    {
        this->SRAM[i] = 0x0;
    }
    for (int i = 0; i < USBRAMSIZE; i++)
    {
        this->USBRAM[i] = 0x0;
    }

}

void memory::initSIO()
{
    for (int i = 0; i < SIOREGISTERS; i++)
    {
        this->SIO[i] = 0x0;
    }
}

short memory::getCPUID()
{
    short ID = (this->SIO[0] & 0x1);
    this->SIO[0] ^= 1UL << 0;
    return ID;
}
