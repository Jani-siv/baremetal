#include "../include/memory.h"


namespace core{
    namespace systemMemory{
        core::memory sysMem;
    }
}
std::uint32_t core::memory::readMemory32(std::uint32_t address)
{
    std::uint32_t data = 0x0;
    for (int i = 0; i < 2; i++)
    {
        data = (data << 16);
        data += this->readMemory((address+(i*2)));
    }
    return data;
}

void core::memory::writeMemory32(std::uint32_t address, const std::uint32_t &value)
{
    std::uint16_t high, low;
    high = value >> 16;
    low = value;
    this->writeMemory(address, high);
    this->writeMemory((address+2), low);
}

std::uint16_t core::memory::readMemory(std::uint32_t address)
{
    std::uint16_t data = 0x0;
    if (address < SRAMBASE)
    {
        data = this->ROM[address];
        data = ( data << 8);
        data += this->ROM[address+1];
        return data;
    }
    else if (address >= SRAMBASE && address < USBRAMBASE)
    {
        address -= SRAMBASE;
        data = this->SRAM[address];
        data = (data << 8);
        data += this->SRAM[address+1];
        return data;
    }
    else if (address >= USBRAMBASE)
    {
        address -= USBRAMBASE;
        data = this->USBRAM[address];
        data = (data << 8);
        data += this->USBRAM[address+1];
        return data;
    }
    std::cout<<"Memory error"<<std::endl;
return 0x0;
}
void core::memory::writeMemory(std::uint32_t address,const std::uint16_t &value)
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

void core::memory::writeRom(const std::uint32_t address,const std::uint16_t &value)
{
    std::cout<<"Writing to rom: "<<std::hex<<static_cast<int>(value)<<std::endl;
    uint8_t low = (value & 0x00FF);
    uint8_t high = (value >> 8) & 0x00FF;
    std::cout<<"writeRom: high "<<std::hex<<static_cast<int>(high)<<std::endl;
    std::cout<<"writeRom: low "<<std::hex<<static_cast<int>(low)<<std::endl;
    std::memcpy(&this->ROM[(address)],&high,sizeof(std::uint8_t));
    std::memcpy(&this->ROM[(address+(1))],&low,sizeof(std::uint8_t));

    std::cout<<"Rom: high "<<std::hex<<static_cast<int>(this->ROM[0])<<std::endl;
    std::cout<<"Rom: low "<<std::hex<<static_cast<int>(this->ROM[1])<<std::endl;
}

void core::memory::writeSram(std::uint32_t address,const std::uint16_t &value)
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

void core::memory::writeUsbram(std::uint32_t address,const std::uint16_t &value)
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

void core::memory::initMemory()
{
    for (auto& i : this->ROM)
    {
      i = 0x0;
    }
    for (auto& i : this->SRAM)
    {
        i = 0x0;
    }
    for (auto& i : this->USBRAM)
    {
        i = 0x0;
    }

    this->initSIO();
}

void core::memory::initSIO()
{
    //skip cpuID
    int j = 0;
    for (auto& i : this->SIO)
    {
        if (j > 0)
        {
            i = 0x0;
        }
        j++;
    }
}

short core::memory::getCPUID()
{
    short ID = (this->SIO[0] & 0x1);
    this->SIO[0] ^= 1UL << 0;
    return ID;
}
